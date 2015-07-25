string replaceBLUE(string str) {
    string ans = "";
    queue<char> q;
    map<char, int> count;
    for (int i = 0; i < str.size(); i++) {
        if (str.at(i) == ' ' && count['B'] > 0 && count['L'] > 0 && count['U'] > 0 && count['E'] > 0
                && (i == 4 || str.at(i - 5) == ' ')) {
            for (int i = 0; i < 4; i++) {
                count[q.front()]--;
                q.pop();
            }
            ans += "XXXX";
        }
        q.push(str.at(i));
        count[str.at(i)]++;
        if (q.size() > 4) {
            count[q.front()]--;
            ans += q.front();
            q.pop();
        }
    }
    if (count['B'] > 0 && count['L'] > 0 && count['U'] > 0 && count['E'] > 0
            && (str.size() == 4 || str.at(str.size() - 5) == ' ')) {
        for (int i = 0; i < 4; i++) {
            count[q.front()]--;
            q.pop();
        }
        ans += "XXXX";
    } else for (int i = 0; i < 4; i++) {
        count[q.front()]--;
        ans += q.front();
        q.pop();
    }
    return ans;
}