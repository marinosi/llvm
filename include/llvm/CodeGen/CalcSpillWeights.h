//===---------------- lib/CodeGen/CalcSpillWeights.h ------------*- C++ -*-===//
//
//                     The LLVM Compiler Infrastructure
//
// This file is distributed under the University of Illinois Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//


#ifndef LLVM_CODEGEN_CALCSPILLWEIGHTS_H
#define LLVM_CODEGEN_CALCSPILLWEIGHTS_H

#include "llvm/CodeGen/MachineFunctionPass.h"
#include "llvm/ADT/DenseMap.h"

namespace llvm {

  class LiveInterval;
  class LiveIntervals;
  class MachineLoopInfo;

  /// normalizeSpillWeight - The spill weight of a live interval is computed as:
  ///
  ///   (sum(use freq) + sum(def freq)) / (K + size)
  ///
  /// @param UseDefFreq Expected number of executed use and def instructions
  ///                   per function call. Derived from block frequencies.
  /// @param Size       Size of live interval as returnexd by getSize()
  ///
  static inline float normalizeSpillWeight(float UseDefFreq, unsigned Size) {
    // The magic constant 200 corresponds to approx. 25 instructions since
    // SlotIndexes allocate 8 slots per instruction.
    //
    // The constant is added to avoid depending too much on accidental SlotIndex
    // gaps for small intervals. The effect is that small intervals have a spill
    // weight that is mostly proportional to the number of uses, while large
    // intervals get a spill weight that is closer to a use density.
    //
    return UseDefFreq / (Size + 200);
  }

  /// VirtRegAuxInfo - Calculate auxiliary information for a virtual
  /// register such as its spill weight and allocation hint.
  class VirtRegAuxInfo {
    MachineFunction &mf_;
    LiveIntervals &lis_;
    const MachineLoopInfo &loops_;
    DenseMap<unsigned, float> hint_;
  public:
    VirtRegAuxInfo(MachineFunction &mf, LiveIntervals &lis,
                   const MachineLoopInfo &loops) :
      mf_(mf), lis_(lis), loops_(loops) {}

    /// CalculateRegClass - recompute the register class for reg from its uses.
    /// Since the register class can affect the allocation hint, this function
    /// should be called before CalculateWeightAndHint if both are called.
    void CalculateRegClass(unsigned reg);

    /// CalculateWeightAndHint - (re)compute li's spill weight and allocation
    /// hint.
    void CalculateWeightAndHint(LiveInterval &li);
  };

  /// CalculateSpillWeights - Compute spill weights for all virtual register
  /// live intervals.
  class CalculateSpillWeights : public MachineFunctionPass {
  public:
    static char ID;

    CalculateSpillWeights() : MachineFunctionPass(ID) {
      initializeCalculateSpillWeightsPass(*PassRegistry::getPassRegistry());
    }

    virtual void getAnalysisUsage(AnalysisUsage &au) const;

    virtual bool runOnMachineFunction(MachineFunction &fn);

  private:
    /// Returns true if the given live interval is zero length.
    bool isZeroLengthInterval(LiveInterval *li) const;
  };

}

#endif // LLVM_CODEGEN_CALCSPILLWEIGHTS_H
