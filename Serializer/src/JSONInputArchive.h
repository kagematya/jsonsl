#pragma once

#include "traits.h"
#include "SizeTag.h"
#include "NameValuePair.h"
#include "rapidjson/document.h"
#include "rapidjson/istreamwrapper.h"
#include <stack>


/**
 * JSON形式を読み取る
 */
class JSONInputArchive {
public:
	JSONInputArchive(std::istream& stream)
		: m_readStream(stream)
		, m_document()
	{
		m_document.ParseStream(m_readStream);
		assert(!m_document.HasParseError());
		assert(!m_document.IsArray());

		m_stack.push(&m_document);	// 最初のノードをルートに設定する
	}

	~JSONInputArchive()
	{
	}


	/**
	 * @note
	 *  配列の処理ではSizeTag処理後に、operator()が次々と呼ばれる事になる
	 *  次の様な処理になっていればok。
	 *		Value[i]をpush --> loadValue --> pop --> i++する（イテレータを進める）
	 *
	 *  また、階層構造に対応するためイテレータ(i)はserialize_arrayの前後でpush/popする
	 */
	template<class T>
	JSONInputArchive& operator()(T& t) {	// 配列読み込み用
		static_assert(!std::is_pointer<T>::value, "Pointer is not serialized");	// ポインタはシリアライズ非対応

		assert(!m_arrayIndexStack.empty());
		int index = m_arrayIndexStack.top();
		
		rapidjson::Value& array_val = *(m_stack.top());	// array
		assert(array_val.IsArray());
		rapidjson::Value& index_val = array_val[index];	// array[i]

		m_stack.push(&index_val);						// array[i]を読み込むため積む
		loadValue(t);
		m_stack.pop();

		index++;
		m_arrayIndexStack.top() = index;	// 読み終えたのでi++して保存
		
		return *this;
	}

	template<class T>
	JSONInputArchive& operator()(NameValuePair<T>& nvp) {
		static_assert(!std::is_pointer<T>::value, "Pointer is not serialized");	// ポインタはシリアライズ非対応

		// keyを探す
		rapidjson::Value::MemberIterator it = m_stack.top()->FindMember(nvp.m_name);
		assert(it != m_stack.top()->MemberEnd());
		
		m_stack.push(&(it->value));
		loadValue(nvp.m_value);
		m_stack.pop();
		
		return *this;
	}

	// 配列のサイズを取得する
	template<class T>
	JSONInputArchive& operator()(SizeTag<T>& sizetag) {
		sizetag.m_size = m_stack.top()->Size();
		return *this;
	}


private:
	void loadValue(bool& b)			{ b = m_stack.top()->GetBool();		}
	void loadValue(int& i)			{ i = m_stack.top()->GetInt();		}
	void loadValue(unsigned& u)		{ u = m_stack.top()->GetUint();		}
	void loadValue(int64_t& i64)	{ i64 = m_stack.top()->GetInt64();	}
	void loadValue(uint64_t& u64)	{ u64 = m_stack.top()->GetUint64();	}
	void loadValue(double& d)		{ d = m_stack.top()->GetDouble();	}
	//void loadValue(const char* s)	{ m_writer.String(s);				}
	void loadValue(std::string& s)	{ s = m_stack.top()->GetString();	}
	//void loadValue(std::nullptr_t&)	{ m_writer.Null();		}

	template<class T, std::enable_if_t<has_memfun_serialize<T, JSONInputArchive>::value>* = nullptr>
	void loadValue(T& t) {	// serializeメンバ関数を持ってればこっちにくる
		t.serialize(*this);
	}

	template<class T, std::enable_if_t<has_fun_serialize<T, JSONInputArchive>::value>* = nullptr>
	void loadValue(T& t) {	// serialize(Arcive&, T&)があるならばこっちにくる
		serialize(*this, t);
	}

	template<class T, std::enable_if_t<has_fun_serialize_array<T, JSONInputArchive>::value>* = nullptr>
	void loadValue(T& t) {	// serialize_array(Arcive&, T&)があるならばこっちにくる
		m_arrayIndexStack.push(0);	// 配列アクセスが行われるので、最初のインデックスを積む
		serialize_array(*this, t);
		m_arrayIndexStack.pop();
	}

private:
	rapidjson::IStreamWrapper m_readStream;
	rapidjson::Document m_document;
	
	std::stack<rapidjson::Value*> m_stack;	// ノードの階層をたどるため、スタックに積んでいく
	std::stack<int> m_arrayIndexStack;		// 配列のインデックスを保存する
};

