#pragma once
#include <iostream>

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

