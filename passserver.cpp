#include "passserver.h"
#include "hashtable.h"

using namespace std;
using namespace cop4530;

PassServer::PassServer(size_t size)
{table.initSize(size);}

PassServer::~PassServer()
{table.clear();}

bool PassServer::load(const char* filename)
{return table.load(filename);}

bool PassServer::addUser(std::pair<string, string> & kv)
{
	string password = encrypt(kv.second);
	pair<string, string> userInfo(kv.first, password);
	return table.insert(userInfo);
}

bool PassServer::addUser(std::pair<string, string> &&kv)
{
	pair<string, string> temp( std::move(kv));
	return addUser(temp);
}

bool PassServer::removeUser(const string &k)
{return table.remove(k);}

bool PassServer::changePassword(const pair<string, string> &p, const string & newpassword)
{
	if (p.second == newpassword)
		return false;
	else if (!table.contains(p.first))
		return false;
	else{
		string oldpass = encrypt(p.second);
		string newpass = encrypt(newpassword);
		pair<string, string> oldInfo(p.first, oldpass);
		if(table.match(oldInfo))
			return false;
		else{
			pair<string, string> newInfo(p.first, newpass);
			table.insert(newInfo);
			return true;
		}
		}
}

bool PassServer::find(const string& user) const
{return table.contains(user);}

void PassServer::dump() const
{table.dump();}

size_t PassServer::size() const
{return table.getSize();}

bool PassServer::write_to_file(const char* filename) const
{return table.write_to_file(filename);}

string PassServer::encrypt(const string & str)
{
	char salt[] = "$1$########";
	string cryptPass = crypt(str.c_str(), salt);
	cryptPass.erase(0,12); //erase the salt for the pass
	return cryptPass;
}
