template<typename K, typename V>
HashTable<K,V>::HashTable(size_t size)
{
	theList.resize(prime_below(size));
	currentSize = 0;
}

template<typename K, typename V>
HashTable<K,V>::~HashTable()
{clear();}

template<typename K, typename V>
bool HashTable<K,V>::contains(const K& k)const
{
	//makeshift itr to traverse the table
	for( auto itr = theList[myhash(k)].begin(); itr != theList[myhash(k)].end(); itr++)
		if(itr->first == k)
			return true;
	
	return false;
}

template<typename K, typename V>
bool HashTable<K,V>::match(const std::pair<K,V> & kv) const
{
	auto & whichList = theList[myhash(kv.first)];
	return std::find(whichList.begin(), whichList.end(), kv) != whichList.end();
}

template<typename K, typename V>
bool HashTable<K,V>::insert(const std::pair<K,V> & kv)
{
	if (match(kv)) //if found ret. false
		return false;
	else if(contains(kv.first))
	{
		auto & whichList = theList[myhash(kv.first)];
		for(auto itr = whichList.begin(); itr != whichList.end(); ++itr)
		{
			if( itr -> first == kv.first)
			{
				auto temp = whichList.erase(itr);
				whichList.insert(temp, kv);
			}
		}
		return true;
	}
	else
	{
		theList[myhash(kv.first)].push_back(kv);
		currentSize++;
		if (currentSize > theList.size())
			rehash();
		return true;
	}
}

template <typename K, typename V>
bool HashTable<K,V>::insert(std::pair<K,V> && kv)
{
	const std::pair<K,V> keyVal = std::move(kv);
	return insert(keyVal);
}

template <typename K, typename V>
bool HashTable<K,V>::remove(const K&k)
{
	auto & whichList = theList[myhash(k)];
	for(auto itr = whichList.begin();itr != whichList.end();itr++)
		if(itr->first == k) 
		{
			itr = whichList.erase(itr);
			currentSize--;
			return true;
		}
	return false;
}

template <typename K, typename V>
void HashTable<K,V>::clear() 
{makeEmpty();}

template <typename K, typename V>
bool HashTable<K,V>::load(const char* filename)
{
	std::pair<K,V> keyVal;
	std::ifstream input;
	input.open(filename, std::ifstream::in);
	
	if(!input)
		return false;
	while(input){
		std::getline(input, keyVal.first, ' ');
		if(isspace(input.peek()))
			input.ignore();
		std::getline(input, keyVal.second, '\n');
		if(isspace(input.peek()))
			input.ignore();
		insert(keyVal);
	}
	input.close();
	return true;
}

template <typename K, typename V>
void HashTable<K,V>::dump()const
{
	for(int i = 0; i< theList.size(); i++)
	{
		std::cout << "v[" << i <<"]:";
		for( auto itr = theList[i].begin(); itr != theList[i].end(); ++itr)
		{
			if(itr != theList[i].begin())
				std::cout <<':';
			std::cout << itr->first << ' ' << itr->second;			
		}
		std::cout << '\n';
	}
}
template <typename K, typename V>
bool HashTable<K,V>::write_to_file(const char* filename) const
{
	std::ofstream output;
	output.open(filename);
	if(!output)
		return false;
	for (int i = 0; i < theList.size(); i++)
		for(auto itr = theList[i].begin(); itr != theList[i].end();itr++)
			output << itr->first << ' ' << itr-> second<< '\n';
		
	output.close();
	return true;
}
template <typename K, typename V>
void HashTable<K,V>::makeEmpty()
{
	for (auto & thisList : theList)
		thisList.clear();
	currentSize = 0;
}
template <typename K, typename V>
void HashTable<K,V>::rehash(){
	auto oldList = theList;
	theList.resize(prime_below(2 * theList.size()));
	
	for(auto & thisList : theList)
		thisList.clear();
	currentSize = 0;
	for(auto & thisList : oldList)
		for(auto & keyVal : thisList)
			insert(std::move(keyVal));
}

template <typename K, typename V>
size_t HashTable<K,V>::myhash(const K &k) const {
	std::hash<K> temp;
	return temp(k) % theList.size();
}
// returns largest prime number <= n or zero if input is too large
// This is likely to be more efficient than prime_above(), because
// it only needs a vector of size n
template <typename K, typename V>
unsigned long HashTable<K,V>::prime_below (unsigned long n)
{
  if (n > max_prime)
    {
      std::cerr << "** input too large for prime_below()\n";
      return 0;
    }
  if (n == max_prime)
    {
      return max_prime;
    }
  if (n <= 1)
    {
		std::cerr << "** input too small \n";
      return 0;
    }

  // now: 2 <= n < max_prime
  std::vector <unsigned long> v (n+1);
  setPrimes(v);
  while (n > 2)
    {
      if (v[n] == 1)
	return n;
      --n;
    }

  return 2;
}

//Sets all prime number indexes to 1. Called by method prime_below(n) 
template <typename K, typename V>
void HashTable<K,V>::setPrimes(std::vector<unsigned long>& vprimes)
{
  int i = 0;
  int j = 0;

  vprimes[0] = 0;
  vprimes[1] = 0;
  int n = vprimes.capacity();

  for (i = 2; i < n; ++i)
    vprimes[i] = 1;

  for( i = 2; i*i < n; ++i)
    {
      if (vprimes[i] == 1)
        for(j = i + i ; j < n; j += i)
          vprimes[j] = 0;
    }
}

template <typename K, typename V>
int HashTable<K,V>::getSize() const
{return currentSize;}

template <typename K, typename V>
void HashTable<K,V>::initSize(int size)
{theList.resize(prime_below(size));}

