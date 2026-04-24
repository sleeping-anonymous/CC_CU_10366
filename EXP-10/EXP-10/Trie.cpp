#include <bits/stdc++.h>
using namespace std;

struct TrieNode {
    TrieNode* children[26];
    bool isEnd;

    TrieNode() {
        isEnd = false;
        for (int i = 0; i < 26; i++)
            children[i] = nullptr;
    }
};

class Trie {
    TrieNode* root;

public:
    Trie() { root = new TrieNode(); }

    // ── Insert ───────────────────────────────────────────────────
    void insert(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx])
                curr->children[idx] = new TrieNode();
            curr = curr->children[idx];
        }
        curr->isEnd = true;
    }

    // ── Search (exact word) ──────────────────────────────────────
    bool search(string word) {
        TrieNode* curr = root;
        for (char c : word) {
            int idx = c - 'a';
            if (!curr->children[idx])
                return false;
            curr = curr->children[idx];
        }
        return curr->isEnd;
    }

    // ── Prefix check ─────────────────────────────────────────────
    bool startsWith(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx])
                return false;
            curr = curr->children[idx];
        }
        return true;
    }

    // ── Delete ───────────────────────────────────────────────────
    bool remove(TrieNode* curr, string& word, int depth) {
        if (!curr) return false;

        if (depth == word.size()) {
            if (!curr->isEnd) return false;   // word doesn't exist
            curr->isEnd = false;
            // safe to delete node if no children
            for (int i = 0; i < 26; i++)
                if (curr->children[i]) return false;
            return true;                      // signal parent to delete this node
        }

        int idx = word[depth] - 'a';
        if (remove(curr->children[idx], word, depth + 1)) {
            delete curr->children[idx];
            curr->children[idx] = nullptr;
            // delete current node only if it's not end of another word
            if (!curr->isEnd) {
                for (int i = 0; i < 26; i++)
                    if (curr->children[i]) return false;
                return true;
            }
        }
        return false;
    }

    void remove(string word) { remove(root, word, 0); }

    // ── Autocomplete (all words with given prefix) ────────────────
    void dfs(TrieNode* curr, string& path, vector<string>& res) {
        if (curr->isEnd) res.push_back(path);
        for (int i = 0; i < 26; i++) {
            if (curr->children[i]) {
                path.push_back('a' + i);
                dfs(curr->children[i], path, res);
                path.pop_back();
            }
        }
    }

    vector<string> autocomplete(string prefix) {
        TrieNode* curr = root;
        for (char c : prefix) {
            int idx = c - 'a';
            if (!curr->children[idx]) return {};
            curr = curr->children[idx];
        }
        vector<string> res;
        string path = prefix;
        dfs(curr, path, res);
        return res;
    }

    // ── Count words with given prefix ────────────────────────────
    int countPrefix(TrieNode* curr, string& word, int depth) {
        if (!curr) return 0;
        if (depth == word.size()) {
            int count = curr->isEnd ? 1 : 0;
            for (int i = 0; i < 26; i++)
                count += countPrefix(curr->children[i], word, depth);
            return count;
        }
        return countPrefix(curr->children[word[depth]-'a'], word, depth+1);
    }

    int countPrefix(string prefix) { return countPrefix(root, prefix, 0); }
};


int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    Trie trie;

    // Insert
    trie.insert("apple");
    trie.insert("app");
    trie.insert("application");
    trie.insert("apt");
    trie.insert("bat");
    trie.insert("ball");

    // Search
    cout << trie.search("app")         << "\n";  // 1 (true)
    cout << trie.search("appl")        << "\n";  // 0 (false — not a complete word)
    cout << trie.startsWith("appl")    << "\n";  // 1 (true — prefix exists)

    // Autocomplete
    vector<string> res = trie.autocomplete("ap");
    for (auto& s : res) cout << s << " ";        // app apple application apt
    cout << "\n";

    // Count words under prefix
    cout << trie.countPrefix("ap")     << "\n";  // 4

    // Delete
    trie.remove("app");
    cout << trie.search("app")         << "\n";  // 0 (deleted)
    cout << trie.search("apple")       << "\n";  // 1 (still exists)

    return 0;
}