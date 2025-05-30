/***
 * Bitwuzla: Satisfiability Modulo Theories (SMT) solver.
 *
 * Copyright (C) 2025 by the authors listed in the AUTHORS file at
 * https://github.com/bitwuzla/bitwuzla/blob/main/AUTHORS
 *
 * This file is part of Bitwuzla under the MIT license. See COPYING for more
 * information at https://github.com/bitwuzla/bitwuzla/blob/main/COPYING
 */

#ifndef BZLA_UTIL_INTEGER_H_INCLUDED
#define BZLA_UTIL_INTEGER_H_INCLUDED

#include <gmpxx.h>

#include <functional>
#include <cstdint>

namespace bzla::util {

class Integer
{
 public:
  /** Construct Integer from mpz_t value. */
  static Integer from_mpz_t(const mpz_t val);

  // Constructors
  Integer();
  Integer(int val);
  Integer(unsigned int val);
  Integer(int64_t val);
  Integer(uint64_t val);
  Integer(const char* val);
  Integer(const std::string& val);

  /** Copy constructor. */
  Integer(const Integer& other);
  /** Move constructor. */
  Integer(Integer&& other);

  /** Destructor. */
  ~Integer();

  // Copy assignment
  Integer& operator=(const Integer& other);
  // Move assignment
  Integer& operator=(Integer&& other);

  // Comparisons
  bool operator==(const Integer& other) const;
  bool operator!=(const Integer& other) const;
  bool operator<(const Integer& other) const;
  bool operator<=(const Integer& other) const;
  bool operator>(const Integer& other) const;
  bool operator>=(const Integer& other) const;

  // Arithmetic operators
  Integer operator+(const Integer& other) const;
  Integer operator-() const;
  Integer operator-(const Integer& other) const;
  Integer operator*(const Integer& other) const;
  Integer operator/(const Integer& other) const;
  Integer operator++(int);
  Integer operator--(int);

  // In-place arithmetic operators
  Integer& operator+=(const Integer& other);
  Integer& operator-=(const Integer& other);
  Integer& operator*=(const Integer& other);
  Integer& operator/=(const Integer& other);
  Integer& operator++();
  Integer& operator--();

  Integer& ipow(uint32_t exp);

  /** Return whether integer is odd. */
  bool is_odd() const;

  /** Compute hash value. */
  size_t hash() const;

  std::string str() const;

  /** Get mpz_t value from Integer class. */
  const mpz_t& gmp_value() const { return d_val_gmp; }
  /**
   * Get uint64_t representation of Integer.
   *
   * Note: This will fail if the stored value does not fit into uint64_t.
   */
  uint64_t to_uint64() const;
  /**
   * Get int64_t representation of Integer.
   *
   * Note: This will fail if the stored value does not fit into int64_t.
   */
  int64_t to_int64() const;

 private:
  mpz_t d_val_gmp;
};

std::ostream& operator<<(std::ostream& os, const Integer& i);

}  // namespace bzla::util

namespace std {

/** Hash function. */
template <>
struct hash<bzla::util::Integer>
{
  size_t operator()(const bzla::util::Integer& i) const;
};

}  // namespace std

#endif
