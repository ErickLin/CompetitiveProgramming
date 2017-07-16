#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <stack>
#include <string>
#include <vector>
using namespace std;

typedef long long ll;

struct TrieNode {
    int depth;
    char c;

    inline bool operator==(const TrieNode& other) const {
        return depth == other.depth && c == other.c;
    }
};

struct Topic {
    size_t name;
    Topic* parent;
    unordered_map<TrieNode*, ll> occurrences;
    unordered_set<TrieNode*> visited;

    inline bool operator==(const Topic& other) const {
        return name == other.name;
    }

    inline bool operator!=(const Topic& other) const {
        return name != other.name;
    }
};

namespace std {
    template<> struct hash<TrieNode> {
        size_t operator()(const TrieNode& trie_node) const {
            return (trie_node.c << 8) + trie_node.depth;
        }
    };

    template<> struct hash<Topic> {
        size_t operator()(const Topic& topic) const {
            return topic.name;
        }
    };
}

void recurse(TrieNode* query, Topic* topic,
             unordered_map<Topic*, unordered_set<Topic*>>& topic_to_children) {
    for (Topic* subtopic : topic_to_children[topic]) {
        if (!subtopic->visited.count(query)) {
            recurse(query, subtopic, topic_to_children);
            subtopic->visited.insert(query);
        }
        topic->occurrences[query] += subtopic->occurrences[query];
    }
}

int main() {
    Topic topic_root;
    unordered_map<size_t, Topic> name_to_topic;
    unordered_map<Topic*, unordered_set<Topic*>> topic_to_children;
    TrieNode trie_root;
    trie_root.depth = 0;
    unordered_map<TrieNode*, unordered_map<char, TrieNode>> trie_node_to_children;

    int n;
    cin >> n;
    Topic* par_topic = &topic_root, *cur_topic;
    int depth = 0, num_topics_parsed = 0;
    while (num_topics_parsed < n || depth) {
        string token;
        cin >> token;
        size_t name = hash<string>()(token);
        if (token == "(") {
            par_topic = cur_topic;
            depth++;
        } else if (token == ")") {
            par_topic = par_topic->parent;
            depth--;
        } else {
            Topic topic;
            topic.name = name;
            topic.parent = par_topic;
            name_to_topic[name] = topic;

            topic_to_children[par_topic].insert(&name_to_topic[name]);
            cur_topic = &name_to_topic[name];
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

        Topic* topic = &name_to_topic[hash<string>()(topic_name)];
        TrieNode* cur_node = &trie_root;
        for (char c : question) {
            if (!trie_node_to_children[cur_node].count(c)) {
                TrieNode child;
                child.depth = cur_node->depth + 1;
                child.c = c;

                trie_node_to_children[cur_node][c] = child;
            }
            cur_node = &trie_node_to_children[cur_node][c];
            topic->occurrences[cur_node]++;
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

        Topic* topic = &name_to_topic[hash<string>()(topic_name)];
        TrieNode* cur_node = &trie_root;
        for (char c : query) {
            cur_node = &trie_node_to_children[cur_node][c];
        }
        if (!topic->visited.count(cur_node)) {
            recurse(cur_node, topic, topic_to_children);
            topic->visited.insert(cur_node);
        }
        cout << topic->occurrences[cur_node] << '\n';
    }
}
