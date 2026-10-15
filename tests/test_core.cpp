#include "../firmware/distance_display/distance.h"
#include <cmath>
#include <cstdlib>
#include <iostream>
static int checks = 0;
#define CHECK(test) do { ++checks; if (!(test)) { std::cerr << "FAIL line " << __LINE__ << "\n"; std::exit(1); } } while (0)

int main() {
  const uint32_t start = 0xfffffff0UL;
  ranging::Filter f; CHECK(!f.read(0).valid); CHECK(!f.push(0, 1166)); CHECK(!f.push(100, 1166));
  CHECK(f.push(200, 5831)); CHECK(f.read(200).valid); CHECK(std::fabs(f.read(200).cm - 20.0f) < 0.1f);
  CHECK(f.read(200).near); CHECK(!f.read(1200).valid);
  CHECK(!f.push(1200, 5831)); CHECK(!f.read(1200).valid); // stale samples cannot resurrect
  f.push(1300, 5831); f.push(1400, 5831); CHECK(f.read(1400).valid); CHECK(!f.read(1400).near);
  CHECK(!f.push(1500, 0)); CHECK(!f.read(1500).valid);
  CHECK(!f.push(1600, 1)); CHECK(!f.push(1700, 100000));
  ranging::Filter rw; rw.push(start, 1166); rw.push(uint32_t(start + 100), 1166);
  rw.push(uint32_t(start + 200), 1166); CHECK(rw.read(uint32_t(start + 201)).valid);
  CHECK(!rw.read(uint32_t(start + 1200)).valid);

  std::cout << "PASS: " << checks << " core checks; no physical hardware tested.\n";
}
