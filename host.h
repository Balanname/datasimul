#ifndef HOST_H
#define HOST_H

#include "address.h"
#include "packet.h"
#include "service.h"
#include <vector>
#include <ctime>

class Host : public Node {
  friend class ServiceInstaller;

private:
  // 호스트의 주소
  Address address_;

  // 설치된 서비스 목록
  std::vector<Service *> services_;

  std::vector<Link *> links_;

public:
  Address address() { return address_; }
  Host(Address address) : address_(address) {}

  bool addservice(Service* service){
    services_.push_back(service);
    return true;
  }

  // 호스트와 설치된 서비스를 전부 초기화한다.
  void initialize();

  Link* getRandomLink(){
    if(links_.empty()){
      return nullptr;
    }
    int index = std::rand() % links_.size();
    return links_[index];
  }

  // 링크를 랜덤으로 하나 선택하여 패킷을 전송한다.
  void send(Packet *packet) {
    getRandomLink()->onReceive(this, packet);
  }

  void onReceive(Packet* packet) override {
    Service *service;
    for(int i = 0; i < services_.size(); i++) {
      Service* s = services_[i];
      if(s->port_ == packet->destPort()) {
        service = s;
        break;
      }
    }

    if(service != nullptr) {
      service->onRecieve(packet);
    }
    else{
      std::cout<<"Host #" << address_.toString() <<": sending packet (from: "
      << packet->srcAddress().toString() << "to: " << packet->destAddress().toString()
      << ", " << packet->data().size() << "byte)" << std::endl;
    }
  } 


  
};

#endif