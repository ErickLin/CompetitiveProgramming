#include <algorithm>
#include <iostream>
#include <list>
#include <vector>
using namespace std;

typedef long long ll;

ll num_subranges_from_len(ll len) {
    return len * (len - 1) / 2;
}

int main() {
    ll n, k;
    cin >> n >> k;
    if (k == 1) {
        for (int i = 0; i < n; i++) {
            cout << "0\n";
        }
        return 0;
    }

    vector<ll> a(n);
    ll inc_range_len = 1, dec_range_len = 1;
    list<ll> inc_range_lens, dec_range_lens;
    for (ll i = 0; i < n; i++) {
        cin >> a[i];
        if (i > 0) {
            if (a[i - 1] == a[i]) {
                inc_range_len++;
                dec_range_len++;
            } else if (a[i - 1] < a[i]) {
                dec_range_lens.push_back(dec_range_len);
                inc_range_len++;
                dec_range_len = 1;
            } else {
                inc_range_lens.push_back(inc_range_len);
                inc_range_len = 1;
                dec_range_len++;
            }
        }
    }
    inc_range_lens.push_back(inc_range_len);
    dec_range_lens.push_back(dec_range_len);

    // Copies of inc_range_lens and dec_range_lens, but will be modified by the
    // tail end of the window rather than the leading end
    list<ll> inc_range_lens_tail(inc_range_lens);
    list<ll> dec_range_lens_tail(dec_range_lens);

    ll cur_num_inc = 0, cur_num_dec = 0;
    ll inc_offset = 0, dec_offset = 0;
    ll inc_len_req = k, dec_len_req = k;
    while (inc_len_req) {
        if (inc_range_lens.front() <= inc_len_req) {
            cur_num_inc += num_subranges_from_len(inc_range_lens.front());
            inc_len_req -= inc_range_lens.front();
            inc_range_lens.pop_front();
        } else {
            inc_offset = inc_len_req;
            cur_num_inc += num_subranges_from_len(inc_offset);
            inc_len_req = 0;
        }
    }
    while (dec_len_req) {
        if (dec_range_lens.front() <= dec_len_req) {
            cur_num_dec += num_subranges_from_len(dec_range_lens.front());
            dec_len_req -= dec_range_lens.front();
            dec_range_lens.pop_front();
        } else {
            dec_offset = dec_len_req;
            cur_num_dec += num_subranges_from_len(dec_offset);
            dec_len_req = 0;
        }
    }
    cout << cur_num_inc - cur_num_dec << '\n';

    for (ll range_end = k + 1; range_end <= n; range_end++) {
        cur_num_inc -= num_subranges_from_len(min(inc_offset, k));
        inc_offset++;
        cur_num_inc += num_subranges_from_len(min(inc_offset, k));
        if (inc_offset == inc_range_lens.front()) {
            inc_offset = 0;
            inc_range_lens.pop_front();
        }

        cur_num_inc -= num_subranges_from_len(min(inc_range_lens_tail.front(),
                                                  k));
        inc_range_lens_tail.front()--;
        cur_num_inc += num_subranges_from_len(min(inc_range_lens_tail.front(),
                                                  k));
        if (!inc_range_lens_tail.front()) {
            inc_range_lens_tail.pop_front();
        }

        cur_num_dec -= num_subranges_from_len(min(dec_offset, k));
        dec_offset++;
        cur_num_dec += num_subranges_from_len(min(dec_offset, k));
        if (dec_offset == dec_range_lens.front()) {
            dec_offset = 0;
            dec_range_lens.pop_front();
        }

        cur_num_dec -= num_subranges_from_len(min(dec_range_lens_tail.front(),
                                                  k));
        dec_range_lens_tail.front()--;
        cur_num_dec += num_subranges_from_len(min(dec_range_lens_tail.front(),
                                                  k));
        if (!dec_range_lens_tail.front()) {
            dec_range_lens_tail.pop_front();
        }

        cout << cur_num_inc - cur_num_dec << '\n';
    }
    return 0;
}
