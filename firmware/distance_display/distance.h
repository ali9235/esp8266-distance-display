#pragma once
#include <stdint.h>

namespace ranging {
struct Reading { bool valid; float cm; bool near; };
class Filter {
 public:
  bool push(uint32_t now, uint32_t pulseUs) {
    if (count_ && uint32_t(now - last_) >= 1000UL) clear();
    // Approximate 343 m/s sound speed, not a calibrated sensor model.
    const float cm = float(pulseUs) * 0.0343f / 2.0f;
    if (pulseUs == 0 || cm < 2.0f || cm > 400.0f) { clear(); return false; }
    values_[next_] = cm; next_ = (next_ + 1) % 5;
    if (count_ < 5) ++count_;
    last_ = now;
    if (count_ < 3) return false;
    float sorted[5];
    for (uint8_t i = 0; i < count_; ++i) sorted[i] = values_[i];
    for (uint8_t i = 1; i < count_; ++i) {
      float value = sorted[i]; int j = int(i) - 1;
      while (j >= 0 && sorted[j] > value) { sorted[j + 1] = sorted[j]; --j; }
      sorted[j + 1] = value;
    }
    median_ = count_ % 2 ? sorted[count_ / 2] :
      (sorted[count_ / 2 - 1] + sorted[count_ / 2]) / 2.0f;
    if (median_ < 30.0f) near_ = true;
    else if (median_ >= 35.0f) near_ = false;
    return true;
  }
  Reading read(uint32_t now) const {
    bool valid = count_ >= 3 && uint32_t(now - last_) < 1000UL;
    return {valid, valid ? median_ : 0.0f, valid && near_};
  }
  void clear() { count_ = next_ = 0; median_ = 0; near_ = false; }
 private:
  float values_[5] = {}, median_ = 0;
  uint8_t count_ = 0, next_ = 0;
  bool near_ = false;
  uint32_t last_ = 0;
};
}  // namespace ranging
