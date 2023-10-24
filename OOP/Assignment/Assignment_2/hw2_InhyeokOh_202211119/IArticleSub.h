#ifndef IArticleSub
#define IArticleSub

#include <iostream>
#include <string>

#include "IArticlePub.h"

using namespace std;

// class IArticlePub;

// class IArticleSub :

class IArticleSub {
    private:
        string sub_name;
        int sub_id;
        string recent_article_contents; 
        IArticlePub* recent_article_pub; 
        IArticlePub* pub_list[5];
        int numOfPub = 0;
        static int static_sub_counter;
    public:
        IArticleSub(string name);
        IArticleSub(string name, IArticlePub* articlePub); 
        ~IArticleSub();
        void Attach(IArticlePub* publisher);
        void AttachResponse(IArticlePub* publisher);
        void Detach(IArticlePub* p_pub);
        void DetachResponse(IArticlePub* p_pub);
        void Update(IArticlePub* publisher, const string contents); 
        void PrintContents();
        string getSubName();
        int getSubID();
        int getPubSize();
        void PrintAllPub();
};

IArticleSub::IArticleSub(const string name) {
    static int static_sub_counter = 0;
    sub_name = name;
    sub_id = ++static_sub_counter;

    // 정보 출력 (원하는 출력 형식 참조)
    cout << "[Constructor] New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;
}

IArticleSub::IArticleSub(const string name, IArticlePub* articlePub) {
    static int static_sub_counter = 0;
    sub_name = name;
    sub_id = ++static_sub_counter;

    // 출판사를 구독자의 목록에 추가
    Attach(articlePub);
    
    // 정보 출력 (원하는 출력 형식 참조)
    cout << "[Constructor] New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;
}

IArticleSub::~IArticleSub() {
    // 모든 출판사의 구독자 목록에서 구독자 제거
    for (int i = 0; i < numOfPub; i++) {
        pub_list[i]->NotifyDetachResponse(this);
    }

    // 정보 출력
    cout << "[Sub] (" << sub_name << "," << sub_id << ") 해지" << endl;
}


void IArticleSub::Attach(IArticlePub* publisher) {
    // 출판사를 구독자의 목록에 추가
    pub_list[numOfPub] = publisher;
    numOfPub++;

    // 대칭적인 관계를 설정하기 위해 출판사에서도 구독자를 추가
    publisher->NotifyAttachResponse(this);
}
void IArticleSub::AttachResponse(IArticlePub* publisher) {
    // 출판사를 구독자의 목록에 추가
    pub_list[numOfPub] = publisher;
    numOfPub++;
}

void IArticleSub::Detach(IArticlePub* p_pub) {
    int index = -1;
    
    // 출판사를 구독자의 목록에서 찾아 제거
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    
    if (index != -1) {
        // 출판사를 제거하고 목록을 재조정
        for (int i = index; i < numOfPub - 1; i++) {
            pub_list[i] = pub_list[i + 1];
        }
        numOfPub--;
        
        // 대칭적인 관계를 설정하기 위해 출판사의 NotifyDetachResponse 함수 호출
        p_pub->NotifyDetachResponse(this);
    } else {
        // 출판사가 목록에 존재하지 않는 경우 오류 메시지 출력
        cout << "Error: 출판사가 구독자의 목록에 존재하지 않습니다." << endl;
    }
}

void IArticlePub::DetachResponse(IArticleSub* subscriber) {
    int index = -1;

    // 구독자를 출판사의 목록에서 찾아 제거
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // 구독자를 제거하고 목록을 재조정
        for (int i = index; i < numOfSub - 1; i++) {
            sub_list[i] = sub_list[i + 1];
        }
        numOfSub--;
    }
}

void IArticleSub::Update(IArticlePub* publisher, const string contents) {
    recent_article_pub = publisher;
    recent_article_contents = contents;
    
    // 최신 정보를 출력하는 PrintContents() 함수 호출
    PrintContents();
}

void IArticleSub::PrintContents() {
    if (recent_article_pub != nullptr) {
        cout << "최신 기사 정보:" << endl;
        cout << "출판사: " << recent_article_pub->getPubName() << endl;
        cout << "내용: " << recent_article_contents << endl;
    } else {
        cout << "아직 최신 기사가 없습니다." << endl;
    }
}

string IArticleSub::getSubName() {
    return sub_name;
}

int IArticleSub::getSubID() {
    return sub_id;
}

int IArticleSub::getPubSize() {
    return numOfPub;
}

void IArticleSub::PrintAllPub() {
    cout << "구독 중인 모든 출판사 목록: ";
    for (int i = 0; i < numOfPub; i++) {
        cout << "[" << pub_list[i]->getPubName() << "," << pub_list[i]->getPubID() << "]";
    }
    cout << endl;
}


#endif