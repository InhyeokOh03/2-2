#include "IArticleSub.h"
#include "IArticlePub.h"

#include <iostream>

using namespace std;

//======================================Sub 함수들==========================================
int IArticleSub::static_sub_counter = 0;


IArticleSub::IArticleSub(const string name) {
    sub_name = name;
    sub_id = ++static_sub_counter;

    cout << "[Constructor] New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;
}

IArticleSub::IArticleSub(const string name, IArticlePub* articlePub) {
    sub_name = name;
    sub_id = ++static_sub_counter;
    cout << "[Constructor] New Sub Created: (" << sub_name << "," << sub_id << ")" << endl;

    Attach(articlePub);
}

IArticleSub::~IArticleSub() {
    cout << "IArticleSub Destructor called" << endl;

    for (int i = 0; i < numOfPub; i++) {
        pub_list[i]->NotifyDetachResponse(this);
    }
}

void IArticleSub::Attach(IArticlePub* publisher) {
    pub_list[numOfPub] = publisher;
    numOfPub++;
    cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
    publisher->NotifyAttachResponse(this);
}

void IArticleSub::AttachResponse(IArticlePub* publisher) {
    pub_list[numOfPub] = publisher;
    numOfPub++;
cout << "[Attach] Pub (" << publisher->getPubName() << "," << publisher->getPubID() << ") is attached to Sub (" << sub_name << "," << sub_id << ")" << endl;
}   

void IArticleSub::Detach(IArticlePub* p_pub) {
    int index = -1;
    // remove
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < numOfPub - 1; i++) {
            pub_list[i] = pub_list[i + 1];
        }
        numOfPub--;
        cout << "[Sub] (" << sub_name << "," << sub_id << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;

        p_pub->NotifyDetachResponse(this);
    } else {
        cout << "Error: There is no publisher in subscribed list." << endl;
    }
}

void IArticleSub::DetachResponse(IArticlePub* p_pub) {
        int index = -1;
    
    for (int i = 0; i < numOfPub; i++) {
        if (pub_list[i] == p_pub) {
            index = i;
            break;
        }
    }
    if (index != -1) {
        for (int i = index; i < numOfPub - 1; i++) {
            pub_list[i] = pub_list[i + 1];
        }
        numOfPub--;
        cout << "[Sub] (" << sub_name << "," << sub_id << ") unsubscribes [Pub] (" << p_pub->getPubName() << "," << p_pub->getPubID() << ")" << endl;
    } else {
        cout << "Error: There is no publisher in subscribed list." << endl;
    }
}

void IArticleSub::Update(IArticlePub* publisher, const string contents) {
    recent_article_pub = publisher;
    recent_article_contents = contents;
    
    PrintContents();
}

void IArticleSub::PrintContents() {
    cout << "Sub (" << sub_name << "," << sub_id << ")'s latest subscribed news is \"" << recent_article_contents << "\" by " << recent_article_pub->getPubName() << endl;
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
    for (int i = 0; i < numOfPub; i++) {
        cout << "[" << pub_list[i]->getPubName() << "," << pub_list[i]->getPubID() << "]";
    }
    cout << endl;
}
