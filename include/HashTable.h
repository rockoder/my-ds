#ifndef HASHTABLE_H
#define HASHTABLE_H

#include <vector>
#include <utility>	// std::pair
#include <algorithm>

template<typename K>
struct sampleHash
{
	int operator()(const K& key)
	{
		return key;
	}
};

// Use functional instead of the thrid template arg.
template <typename K, typename V, typename F = sampleHash<K>>
class HashTable
{
public:
	HashTable(size_t size)
		: table_(size)
	{	}

	V get(const K& key)
	{
		size_t hash = hashCode(key);
		
		auto it = std::find_if(table_[hash].begin(), table_[hash].end(), 
						[&key](const std::pair<K, V>& p){ return p.first == key;});

		return it->second; 	
	}

	void put(const K& key, const V& value)
	{
		size_t hash = hashCode(key);

		if (hash >= 0 and hash < table_.size())
		{
			// TODO: decltype(*(table_[hash].begin())) -- this should give
			// constant reference.
			auto it = std::find_if(table_[hash].begin(), table_[hash].end(), 
						[&key](decltype(*(table_[hash].begin())) ele){ return ele.first == key;});

			if (it == table_[hash].end())
			{
				table_[hash].push_back(std::make_pair(key, value));
			}
			else
			{
				it->second = value;
			}
		}
		else
		{
			// TODO
		}
	}

private:
	std::vector<std::vector<std::pair<K, V>>> table_;
	F hashCode;
};

#endif