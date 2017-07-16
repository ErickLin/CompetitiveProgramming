#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

struct Topic {
    int depth = 0;
    string name;
    Topic* parent;

    inline bool operator==(const Topic& other) const {
        return name == other.name;
    }

    inline bool operator!=(const Topic& other) const {
        return name != other.name;
    }
};

struct TopicPtrCmp {
    bool operator()(const Topic* lhs, const Topic* rhs) const {
        if (lhs->depth == rhs->depth) {
            return lhs->name < rhs->name;
        }
        return lhs->depth > rhs->depth;
    }
};

struct TrieNode {
    int depth = 0;
    char c;
    unordered_map<Topic*, ll> occurrences_by_topic;
    set<Topic*, TopicPtrCmp> working_topics;

    inline bool operator==(const TrieNode& other) const {
        return depth == other.depth && c == other.c;
    }
};

namespace std {
    template<> struct hash<Topic> {
        size_t operator()(const Topic& topic) const {
            return hash<string>()(topic.name);
        }
    };

    template<> struct hash<TrieNode> {
        size_t operator()(const TrieNode& trie_node) const {
            return (trie_node.c << 8) + trie_node.depth;
        }
    };
}

int main() {
    Topic topic_root;
    unordered_map<string, Topic> name_to_topic;
    unordered_map<Topic*, unordered_set<Topic*>> topic_to_children;
    TrieNode trie_root;
    unordered_map<TrieNode*, unordered_map<char, TrieNode>>
        trie_node_to_children;

    int n;
    cin >> n;
    Topic* par_topic = &topic_root, *cur_topic;
    int depth = 0, num_topics_parsed = 0;
    while (num_topics_parsed < n || depth) {
        string token;
        cin >> token;
        if (token == "(") {
            par_topic = cur_topic;
            depth++;
        } else if (token == ")") {
            par_topic = par_topic->parent;
            depth--;
        } else {
            Topic topic;
            topic.depth = depth;
            topic.name = token;
            topic.parent = par_topic;
            name_to_topic[token] = topic;

            topic_to_children[par_topic].insert(&name_to_topic[token]);
            cur_topic = &name_to_topic[token];
            num_topics_parsed++;
        }
    }

    int m;
    cin >> m;
    for (int i = 0; i < m; i++) {
        string topic_name;
        cin >> topic_name;
        topic_name.pop_back();
        cin.ignore();
        string question;
        getline(cin, question);

        Topic* topic = &name_to_topic[topic_name];
        TrieNode* cur_node = &trie_root;
        for (char c : question) {
            if (!trie_node_to_children[cur_node].count(c)) {
                TrieNode child;
                child.depth = cur_node->depth + 1;
                child.c = c;

                trie_node_to_children[cur_node][c] = child;
            }
            cur_node = &(trie_node_to_children[cur_node][c]);
            cur_node->occurrences_by_topic[topic]++;
            cur_node->working_topics.insert(topic);
        }
    }

    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        string topic_name;
        cin >> topic_name;
        cin.ignore();
        string query;
        getline(cin, query);

        Topic* topic = &name_to_topic[topic_name];
        TrieNode* node = &trie_root;
        for (char c : query) {
            node = &(trie_node_to_children[node][c]);
        }

        if (!node->working_topics.empty()) {
            Topic* cur_topic;
            while ((cur_topic = *(node->working_topics.begin()))->depth >
                    topic->depth) {
                node->working_topics.erase(cur_topic);
                node->occurrences_by_topic[cur_topic->parent] +=
                        node->occurrences_by_topic[cur_topic];
                node->working_topics.insert(cur_topic->parent);
            }
        }
        /*
        set<Topic*, TopicPtrCmp> working_topics_copy(
                node->working_topics.begin(), node->working_topics.end());
        unordered_set<Topic*> visited;
        for (Topic* working_topic : node->working_topics) {
            if (working_topic->depth > topic->depth) {
                working_topics_copy.erase(working_topic);

                Topic* cur_topic = working_topic;
                while (cur_topic->depth > topic->depth &&
                        !visited.count(cur_topic)) {
                    visited.insert(cur_topic);
                    node->occurrences_by_topic[cur_topic->parent] +=
                            node->occurrences_by_topic[cur_topic];
                    cur_topic = cur_topic->parent;
                }
                if (!visited.count(cur_topic)) {
                    working_topics_copy.insert(cur_topic);
                }
            }
        }
        node->working_topics = working_topics_copy;
        */

        cout << node->occurrences_by_topic[topic] << '\n';
    }
}
