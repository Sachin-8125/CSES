#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n;
    if (!(cin >> n)) return 0;

    vector<int> r(n);
    for (int i = 0; i < n; ++i) {
        cin >> r[i];
    }

    long long main_scaled_sum = 0;
    __float128 micro_fraction_sum = 0.0;

    for (int i = 0; i < n; ++i) {
        for (int j = i + 1; j < n; ++j) {
            long long favorable = 0;
    
            if (r[i] <= r[j]) {
                favorable = (long long)r[i] * (r[i] - 1) / 2;
            } else {
                favorable = (long long)r[j] * (r[j] - 1) / 2 + (long long)r[j] * (r[i] - r[j]);
            }
            
            long long current_denominator = r[i] * r[j];
            long long scaled_numerator = favorable * 1000000LL;
            
            main_scaled_sum += (scaled_numerator / current_denominator);
            
            long long division_remainder = scaled_numerator % current_denominator;
            micro_fraction_sum += (__float128)division_remainder / current_denominator;
        }
    }

    long long overflow = (long long)micro_fraction_sum;
    main_scaled_sum += overflow;
    micro_fraction_sum -= overflow;

    if (micro_fraction_sum > 0.5) {
        main_scaled_sum++;
    } else if (micro_fraction_sum == 0.5) {
        if (main_scaled_sum % 2 != 0) {
            main_scaled_sum++;
        }
    }

    long long final_integral = main_scaled_sum / 1000000;
    long long final_fractional = main_scaled_sum % 1000000;

    cout << final_integral << "." << setfill('0') << setw(6) << final_fractional << "\n";

    return 0;
}