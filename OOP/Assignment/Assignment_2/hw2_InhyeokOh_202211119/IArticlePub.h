#ifndef IArticlePub
#define IArticlePub

#include <iostream>
#include <string>

#include "IArticleSub.h"

using namespace std;

// class IArticleSub;

// class IArticlePub :

class IArticlePub {
private:
    string pub_name;
    int pub_id;
    string recent_contents;
    IArticleSub* sub_list[5];
    int numOfSub = 0;
    static int static_pub_counter;
public:
    IArticlePub(const string name);
    IArticlePub(string name, const string con);
    ~IArticlePub();
    void NotifyAttach(IArticleSub* subscriber);
    void NotifyAttachResponse(IArticleSub* subscriber); 
    void NotifyDetach(IArticleSub* subscriber);
    void NotifyDetachResponse(IArticleSub* subscriber); 
    void updatePubContents(string c);
    void Notify();
    int getPubID();
    string getPubName();
    int getSubSize();
    void PrintAllSub();
};

IArticlePub::IArticlePub(const string name) : pub_name(name) {
    static_pub_counter++;
    pub_id = static_pub_counter;
    recent_contents = "";
    numOfSub = 0;

    cout << "[Constructor] New Pub Created: (" << pub_name << "," << pub_id << ")" << endl;
}

IArticlePub::IArticlePub(const string name, const string con) : pub_name(name), recent_contents(con) {
    static_pub_counter++;
    pub_id = static_pub_counter;
    numOfSub = 0;

    cout << "[Constructor] New Pub Created: (" << pub_name << "," << pub_id << ")" << endl;
}

IArticlePub::~IArticlePub() {
    // 1. 모든 구독자의 publisher 리스트(pub_list)에서 현재 Publisher 제거
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->DetachResponse(this);
    }

    // 2. 적절한 정보 출력
    cout << "IArticlePub 소멸자 호출됨" << endl;
}


void IArticlePub::NotifyAttach(IArticleSub* subscriber) {
    // 이미 구독자인지 확인
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // 새로운 구독자를 추가
    if (numOfSub < 5) { // 최대 5명의 구독자까지만 추가 가능
        sub_list[numOfSub] = subscriber;
        numOfSub++;

        // 대칭적인 연결 (Subscriber의 pub_list에도 Publisher 추가)
        subscriber->AttachResponse(this);

        // 알림 메시지 출력
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyAttachResponse(IArticleSub* subscriber) {
    // 이미 구독자인지 확인
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // 새로운 구독자를 추가
    if (numOfSub < 5) { // 최대 5명의 구독자까지만 추가 가능
        sub_list[numOfSub] = subscriber;
        numOfSub++;

        // 대칭적인 연결 (Subscriber의 pub_list에도 Publisher 추가)
        subscriber->Attach(this);

        // 알림 메시지 출력
        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyDetach(IArticleSub* subscriber) {
    bool found = false;

    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            found = true;

            for (int j = i; j < numOfSub - 1; j++) {
                sub_list[j] = sub_list[j + 1];
            }
            numOfSub--;

            subscriber->DetachResponse(this);

            cout << "[Detach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is detached from Pub (" << pub_name << "," << pub_id << ")" << endl;
        }
    }

    if (!found) {
        cout << "Error: Subscriber " << subscriber->getSubName() << " is not in the publisher's subscriber list." << endl;
    }
}

void IArticlePub::NotifyDetachResponse(IArticleSub* subscriber) {
    bool found = false;

    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            found = true;

            for (int j = i; j < numOfSub - 1; j++) {
                sub_list[j] = sub_list[j + 1];
            }
            numOfSub--;

            subscriber->Detach(this);

            cout << "[Detach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is detached from Pub (" << pub_name << "," << pub_id << ")" << endl;
        }
    }

    if (!found) {
        cout << "Error: Subscriber " << subscriber->getSubName() << " is not in the publisher's subscriber list." << endl;
    }
}

void IArticlePub::updatePubContents(string c) {
    recent_contents = c;
    Notify();
}

void IArticlePub::Notify() {
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->Update(this, recent_contents);
    }
}

int IArticlePub::getPubID() {
    return pub_id;
}

string IArticlePub::getPubName() {
    return pub_name;
}

int IArticlePub::getSubSize() {
    return numOfSub;
}

void IArticlePub::printAllSub() {
    cout << "All Sub of (" << pub_name << "," << pub_id << "): ";
    for (int i = 0; i < numOfSub; i++) {
        cout << "[" << sub_list[i]->getSubName() << "," << sub_list[i]->getSubID() << "]";
    }
    cout << endl;
}



#endif