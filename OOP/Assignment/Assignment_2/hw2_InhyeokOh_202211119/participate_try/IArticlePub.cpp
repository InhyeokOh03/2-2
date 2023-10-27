#include "IArticlePub.h"
#include "IArticleSub.h"

#include <iostream>

using namespace std;

//======================================Pub 함수들==========================================
int IArticlePub::static_pub_counter = 0;

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
    cout << "IArticlePub Destructor called" << endl;
    for (int i = 0; i < numOfSub; i++) {
        sub_list[i]->DetachResponse(this);
    }
}

void IArticlePub::NotifyAttach(IArticleSub* subscriber) {
    // Are you subscriber?
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // Add neww subscriber
    if (numOfSub < 5) { // under 5
        sub_list[numOfSub] = subscriber;
        numOfSub++;

        cout << "[Attach] Sub (" << subscriber->getSubName() << "," << subscriber->getSubID() << ") is attached to Pub (" << pub_name << "," << pub_id << ")" << endl;
        subscriber->AttachResponse(this);
    } else {
        cout << "Error: Maximum number of subscribers reached for the publisher." << endl;
    }
}

void IArticlePub::NotifyAttachResponse(IArticleSub* subscriber) {
    // Are you subscriber?
    for (int i = 0; i < numOfSub; i++) {
        if (sub_list[i] == subscriber) {
            cout << "Error: Subscriber " << subscriber->getSubName() << " is already in the publisher's subscriber list." << endl;
            return;
        }
    }

    // Add new subscriber
    if (numOfSub < 5) { // under 5.
        sub_list[numOfSub] = subscriber;
        numOfSub++;
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
            cout << "[Pub] (" << pub_name << "," << pub_id << ") detach [Sub] (" << subscriber->getSubName() << "," << subscriber->getSubID() << ")" << endl;
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

void IArticlePub::PrintAllSub() {
    // cout << "All Sub of (" << pub_name << "," << pub_id << "): ";
    for (int i = 0; i < numOfSub; i++) {
        cout << "[" << sub_list[i]->getSubName() << "," << sub_list[i]->getSubID() << "]";
    }
    cout << endl;
}
