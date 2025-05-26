#pragma once


using namespace std;

namespace hash_bucket
{
	template<class T>
	struct HashNode
	{
		T _data;
		HashNode<T>* _next;//保存下一个链接的节点
		HashNode(T& data)  //构造函数传入data来进行构造节点和存入
			:_data(data)
			, _next(nullptr)
		{
		}
	};
	template<class K, class T, class KeyOfT, class Hash>//利用上一层的MyUnordered传过来的
	class HashTable
	{
		typedef HashNode<T> Node;
		//引入一个开辟空间大小的原则
		inline unsigned long __stl_next_prime(unsigned long n)
		{
			// Note: assumes long is at least 32 bits.
			static const int __stl_num_primes = 28;
			static const unsigned long __stl_prime_list[__stl_num_primes] =
			{
				53, 97, 193, 389, 769,
				1543, 3079, 6151, 12289, 24593,
				49157, 98317, 196613, 393241, 786433,
				1572869, 3145739, 6291469, 12582917, 25165843,
				50331653, 100663319, 201326611, 402653189, 805306457,
				1610612741, 3221225473, 4294967291
			};
			const unsigned long* first = __stl_prime_list;
			const unsigned long* last = __stl_prime_list + __stl_num_primes;
			const unsigned long* pos = lower_bound(first, last, n);
			return pos == last ? *(last - 1) : *pos;
		}
	public:
		HashTable()
		{
			//构造函数先开辟空间
			_tables.resize(__stl_next_prime(_tables.size()), nullptr);
		}
		~HashTable()
		{
			for (size_t i = 0; i < _tables.size(); i++)
			{
				Node* cur = _tables[i];
				while (cur)
				{
					Node* next = cur->_next;
					delete cur;
					cur = next;
				}
				_tables[i] = nullptr;
			}
		}

		Node* Find(K& key)
		{
			Hash hs;
			size_t hashi = hs(key) % _tables.size();
			Node* cur = _tables[hashi];
			while (cur)
			{
				if(cur->_kv.first==key)
				{
					return cur;
				}
				cur = cur->_next;
			}
			return nullptr;
		}

		bool Insert(T& data)
		{
			KeyOfT kot;
			if (Find(kot(data)))
				return false;
			Hash hs;
			size_t hashi = hs(kot(data)) % _tables.size();
			//检查是否需要扩容
			if (_n == _tables.size())
			{
				//创建新的vector, 把数据移至到新的Table后, 交换新旧table,编译器会自己删除旧的table
				vector<Node*> newtables(__stl_next_prime(unsigned long n));
			}
			//采用头插法,把新节点的下一个节点置为链表第一个数据,再将第一个数据改为newnode
			Node* newnode = new Node(data);
			newnode->_next = _tables[hashi];
			_tables[hashi] = newnode;
			++_n;
			return true;


		}
	private:
		vector<Node*> _tables;
		size_t _n = 0;			//存储数据个数
	};
}
template <class K>
struct HashFunc
{
	size_t operator()(const K& key)
	{
		return (size_t)key
			vbvcb
			;


		
	}
	
};

