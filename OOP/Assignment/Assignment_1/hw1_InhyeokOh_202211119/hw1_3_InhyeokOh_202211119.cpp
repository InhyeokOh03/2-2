#include <iostream>
#include <cstring>

using namespace std;
// you can use any header files that you learned in the lecture so far. using namespace std;
char** special_filter(const char* sentences[], int filter_offset, int num_sentences) {
    char** filtered_sentences = new char*[num_sentences];

    for (int i = 0; i < num_sentences; i++) {
        const char* sentence = sentences[i];
        int sentence_length = strlen(sentence);
        char* filtered_sentence = new char[sentence_length + 1];

        for (int j = 0; j < sentence_length; j++) {
            char jth_char = sentence[j];

            if ((jth_char >= 'a' && jth_char <= 'z') || (jth_char >= 'A' && jth_char <= 'Z')) {
            
                char pivot = (jth_char >= 'a' && jth_char <= 'z') ? 'a' : 'A';

                int index = jth_char - pivot + 1;

                if (index <= filter_offset) {
                    filtered_sentence[j] = jth_char;
                }
                else {
                    filtered_sentence[j] = '#';
                }
            }
            else {
                filtered_sentence[j] = jth_char;
            }
        }
        // cout << "Filtered Sentence " << i + 1 << ": " << filtered_sentence << endl;
        filtered_sentence[sentence_length] = '\0';
        filtered_sentences[i] = filtered_sentence;
    }
    // cout << "Filtered_sentences:" << endl;
    // for (int i = 0; i < num_sentences; i++) {
    //     cout << filtered_sentences[i] << endl;
    // }
    return filtered_sentences;
}

int main() {
    const char* sentences[] = {"Hello bruhs", "I am ABCDEFGHIJKLMNOPQRSTUBWXYZ"}; 
    int num_sentences = 2;
    char** result = special_filter(sentences, 25, num_sentences);
    for (int i = 0; i < num_sentences; i++) {
        cout << result[i] << endl; 
    }
    return 0; 
}