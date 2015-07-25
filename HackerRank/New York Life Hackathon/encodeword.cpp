string encode(vector<int> p, int k, string s) {
    for (int i = 0; i < p.size(); i++) {
        p[i]--;
    }
    vector<int> cycleLen(s.size());
    fill(cycleLen.begin(), cycleLen.end(), -1);
    for (int i = 0; i < s.size(); i++) {
        int current = i;
        for (int j = 1; j <= s.size() && cycleLen[i] == -1; j++) {
            current = p[current];
            if (current == i) {
                cycleLen[i] = j;
            }
        }
        cout << cycleLen[i] << ' ';
    }
    string ans = "";
    for (int i = 0; i < s.size(); i++) {
        string prev = s;
        for (int j = 0; j < k % cycleLen[i]; j++) {
            string current = "";
            for (int k = 0; k < s.size(); k++) {
                current += prev.at(p[k]);
            }
            prev = current;
        }
        ans += prev[i];
    }
    return ans;
}