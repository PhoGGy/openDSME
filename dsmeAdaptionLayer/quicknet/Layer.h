/*
 * openDSME
 *
 * Implementation of the Deterministic & Synchronous Multi-channel Extension (DSME)
 * introduced in the IEEE 802.15.4e-2012 standard
 *
 * Authors: Florian Meier <florian.meier@tuhh.de>
 *          Maximilian Koestler <maximilian.koestler@tuhh.de>
 *          Sandrina Backhauss <sandrina.backhauss@tuhh.de>
 *
 * Based on
 *          DSME Implementation for the INET Framework
 *          Tobias Luebkert <tobias.luebkert@tuhh.de>
 *
 * Copyright (c) 2015, Institute of Telematics, Hamburg University of Technology
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of the Institute nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE INSTITUTE AND CONTRIBUTORS ``AS IS'' AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
 * ARE DISCLAIMED.  IN NO EVENT SHALL THE INSTITUTE OR CONTRIBUTORS BE LIABLE
 * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
 * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
 * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
 * LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
 * OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#ifndef QUICKNET__LAYER_H_
#define QUICKNET__LAYER_H_

#include "./Matrix.h"
#include "./Vector.h"
#include "../../../dsme_platform.h"

namespace dsme {

namespace quicknet {


typedef void (*activation_t)(Vector<float>&);

template<typename T>
class Layer {
public:
    Layer(const Matrix<T>& weights, const Vector<T>& bias, Vector<T>& output, activation_t activation): weights{weights}, bias{bias}, output{output}, activation{activation} {
        DSME_ASSERT(output.length() == bias.length());
        DSME_ASSERT(output.length() == weights.rows());
    }

    Layer(const Layer&) = delete;
    Layer& operator=(const Layer&) = delete;
    ~Layer() = default;

    Vector<T>& feedForward(Vector<T>& input) {
        DSME_ASSERT(input.length() == this->weights.columns());

        this->weights.mult(input, this->output);
        for(uint8_t i = 0; i < this->output.length(); i++) {
            this->output(i) += this->bias(i);
        }   

        if(this->activation) {
            activation(this->output);
        }

        return this->output;
    }


private:
    const Matrix<T>& weights;
    const Vector<T>& bias;
    Vector<T>& output;
    const activation_t activation;
};

} /* namespace quicknet */

} /* namespace dsme */

#endif /* QUICKNET__LAYER_H_ */