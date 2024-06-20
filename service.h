#ifndef SERVICE_H
#define SERVICE_H

#include "node.h"

class Host;

class Service {
  friend class ServiceInstaller;

public:
  // 서비스가 설치된 호스트
  Host *host_;

  // 서비스가 사용하는 포트
  short port_;

  Service(Host *host, int port) : host_(host), port_(port) {}
  
  //Host에 설치된 프로그램을 나타낸 클래스다. 하나의 포트를 사용하며, 패킷을 생성하여 전송하거나 자신에게 온 패킷을 처리한다.

 

  
};

#endif
