#include "common.h"
#include "HttpProtocol.h"

int main()
{
	CHttpProtocol MyHttpObj;
	MyHttpObj.StartHttpSrv();
	while (1)
		sleep(1000);
	return 0;
}
