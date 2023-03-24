//   Copyright 2023 <Huawei Technologies Co., Ltd>
//
//   Licensed under the Apache License, Version 2.0 (the "License");
//   you may not use this file except in compliance with the License.
//   You may obtain a copy of the License at
//
//       http://www.apache.org/licenses/LICENSE-2.0
//
//   Unless required by applicable law or agreed to in writing, software
//   distributed under the License is distributed on an "AS IS" BASIS,
//   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
//   See the License for the specific language governing permissions and
//   limitations under the License.

#ifndef MATH_OPERATORS_QUBIT_OPERATOR_VIEW_HPP_
#define MATH_OPERATORS_QUBIT_OPERATOR_VIEW_HPP_
#include <cstdint>
#include <map>

#include "math/tensor/ops.hpp"
#include "math/tensor/ops/memory_operator.hpp"
#include "math/tensor/tensor.hpp"
namespace operators::qubit {
namespace tn = tensor;
enum class TermValue : uint8_t {
    //! DO NOT CHANGE VALUE.
    I = 0,
    X = 1,
    Y = 2,
    Z = 3,
};

using pauli_product_map_t = std::map<TermValue, std::map<TermValue, std::tuple<tn::Tensor, TermValue>>>;

// clang-format off
const pauli_product_map_t pauli_product_map = {
    {
            TermValue::I, {
                            {TermValue::I, {tn::ops::ones(1), TermValue::I}},
                            {TermValue::X, {tn::ops::ones(1), TermValue::X}},
                            {TermValue::Y, {tn::ops::ones(1), TermValue::Y}},
                            {TermValue::Z, {tn::ops::ones(1), TermValue::Z}},
                          }
        },
    {
            TermValue::X, {
                            {TermValue::I, {tn::ops::ones(1), TermValue::X}},
                            {TermValue::X, {tn::ops::ones(1), TermValue::I}},
                            {TermValue::Y, {tn::ops::init_with_value(std::complex<double>(0.0, 1.0)), TermValue::Z}},
                            {TermValue::Z, {tn::ops::init_with_value(std::complex<double>(0.0, -1.0)), TermValue::Y}},
                          }
        },
    {
            TermValue::Y, {
                            {TermValue::I, {tn::ops::ones(1), TermValue::Y}},
                            {TermValue::X, {tn::ops::init_with_value(std::complex<double>(0.0, -1.0)), TermValue::Z}},
                            {TermValue::Y, {tn::ops::ones(1), TermValue::I}},
                            {TermValue::Z, {tn::ops::init_with_value(std::complex<double>(0.0, 1.0)), TermValue::X}},
                          }
        },
    {
            TermValue::Z, {
                            {TermValue::I, {tn::ops::ones(1), TermValue::Z}},
                            {TermValue::X, {tn::ops::init_with_value(std::complex<double>(0.0, 1.0)), TermValue::Y}},
                            {TermValue::Y, {tn::ops::init_with_value(std::complex<double>(0.0, -1.0)), TermValue::X}},
                            {TermValue::Z, {tn::ops::ones(1), TermValue::I}},
                          }
        },
};
// clang-format on

struct QubitView {
    tn::Tensor coeff = tn::ops::ones(1);
    std::vector<uint64_t> pauli_string{};

    // -----------------------------------------------------------------------------

    QubitView() = default;
    void InplaceMulPauli(TermValue term, size_t idx) {
        if (term == TermValue::I) {
            return;
        }
        size_t group_id = idx >> 5;
        size_t local_id = ((idx & 31) << 1) + 1;
        if (this->pauli_string.size() < group_id + 1) {
            for (size_t i = pauli_string.size(); i < group_id; i++) {
                this->pauli_string.push_back(0);
            }
            pauli_string[group_id] = pauli_string[group_id]&
        }
    }
};

}  // namespace operators::qubit
#endif /* MATH_OPERATORS_QUBIT_OPERATOR_VIEW_HPP_ */
