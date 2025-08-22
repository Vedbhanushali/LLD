#include<iostream>
#include<unordered_map>
#include<vector>
#include<memory>

using namespace std;

/* ---------------- Helper functions ---------------- */
// lowercase tokenize words
static inline string toLower(const string& str) {
    string result;
    for(char c : str) {
        result += tolower(c);
    }
    return result;
}
// tokenize a string into words
static inline vector<string> tokenize(const string& str) {
    string s = toLower(str);
    vector<string> tokens;
    string curr;
    for(char &c : s) {
        if(isalnum(c)) {
            curr.push_back(c);
        } else {
            if(!curr.empty()) continue;
            tokens.emplace_back(curr);
            curr.clear();
        }
    }
}
class Page {
    int id;
    string title;
    string content;
    public:
    Page(int id, const string title, const string content):id(id), title(title), content(content) {}
    ~Page() = default;
    int getId() const {
        return id;
    }
    string getTitle() const {
        return title;
    }
    string getContent() const {
        return content;
    }
};
class TrieNode {
    public:
    bool isTerminal;
    unordered_map<char, shared_ptr<TrieNode>> children;
    unordered_map<int,int> tokenBelongsToPageTimes; // pageId -> times
    TrieNode() {
        isTerminal = false;
    }
    ~TrieNode() {
        for(auto &child : children) {
            if(child.second) child.second.reset();
        }
        children.clear();
        tokenBelongsToPageTimes.clear();
    }
};

class TrieService {
    shared_ptr<TrieNode> root;
    public:
    TrieService() {
        root = make_shared<TrieNode>();
    }
    ~TrieService() {
        if(root) root.reset();
    }
    void indexPage(const shared_ptr<Page> page) {
        vector<string> tokens = tokenize(page->getContent());
        for(const string& token : tokens) {
            addToken(token,page->getId());
        }
    }
    void addToken(const string&token,int pageId) {
        if(token.empty()) return;
        shared_ptr<TrieNode> current = root;
        for(char c : token) {
            if(current->children.find(c) == current->children.end()) {
                //not found in children, create a new node
                current->children[c] = make_shared<TrieNode>();
            }
            current = current->children[c];
        }
        //reach the end of the token and trienode
        current->isTerminal = true; // mark the end of a token
        current->tokenBelongsToPageTimes[pageId]++; // increment the count for this page
    }
    // token -> <pageId -> times>
    unordered_map<int,int>* TokenPageMapping(const string & token) {
        if(token.empty()) return nullptr;
        shared_ptr<TrieNode> current = root;
        for(char c : token) {
            if(current->children.find(c) == current->children.end()) {
                //not found in children, token doesn't exist
                return nullptr;
            }
            current = current->children[c];
        }
        if(current->isTerminal) {
            return &(current->tokenBelongsToPageTimes);
        }
        return nullptr;
    }
};

class SearchEngine {
    vector<shared_ptr<Page>> pages;
    shared_ptr<TrieService> trieService;
    public:
    SearchEngine(): trieService(make_shared<TrieService>()){}
    void addPage(shared_ptr<Page> page) {
        pages.push_back(page);
    }
    void indexAllPages() {
        //indexing all pages
        for(const auto& page : pages) {
            trieService->indexPage(page);
        }
    }
    // AND search -> all terms must be present in page
    // returns vector of (pageId, score)
    vector<pair<int,int>> AndSearch(const string &query) {
        vector<string> tokens = tokenize(query);
        if(tokens.empty()) return {};


    }
};

int main() {
    SearchEngine se;

    // Dummy pages 
    se.addPage(make_shared<Page>(1, "C++ Search Engine", "We build a tiny search se with a trie and inverted index in cpp."));
    se.addPage(make_shared<Page>(2, "Intro to Programming", "Programming basics include variables, loops, and data structures like the trie."));
    se.addPage(make_shared<Page>(3, "Data Science with Python", "Python is great for data science, but C++ (cpp) is powerful for performance."));
    se.addPage(make_shared<Page>(4, "Information Retrieval", "Search engines use indexing, ranking, tf-idf, and bm25 to score documents."));
    se.addPage(make_shared<Page>(5, "Object Oriented C++", "C++ supports classes, objects, and object oriented programming concepts."));

    se.indexAllPages();

    cout << "Enter query (space-separated terms, empty line to quit):\n";
    string line;
    while (true) {
        cout << "> ";
        if (!getline(cin, line)) break;
        if (line.empty()) break;

        auto results = se.AndSearch(line);
        if (results.empty()) {
            cout << "No results.\n";
            continue;
        }

    //     for (auto& r : results) {
    //         const Page* p = se.getPageById(r.first);
    //         if (!p) continue;
    //         cout << "docId=" << p->id
    //              << " score=" << r.second
    //              << " | " << p->title << "\n"
    //              << "  " << MiniSearchEngine::snippet(p->content) << "\n";
    //     }
    }

    return 0;
}