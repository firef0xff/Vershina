#ifndef SQLH
#define SQLH
#include <ADODB.hpp>


//#define NODB;
class cSQL
{
public:
		cSQL(TADOConnection * Connection);
		cSQL(cSQL * r);
		~cSQL();
	void SetConnection (TADOConnection * Connection){url=Connection;};
	void SetReconnectCount(int count){ReconnectCount=count;};
	int GetReconnectCount(){return ReconnectCount;}
	TADOConnection* GetConnect()const {return url;}
	bool CheckConnection();
	bool Connect ();
	TADOQuery * SendSQL(const String &request);
	bool SendCommand(const String &request);
private:
	bool TestConnectoin() const;
	TADOConnection *url;
	TADOCommand *cmd;
	int ReconnectCount;
};
#endif
