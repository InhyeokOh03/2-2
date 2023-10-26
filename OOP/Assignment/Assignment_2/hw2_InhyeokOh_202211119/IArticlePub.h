#pragma once
#include <iostream>

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

