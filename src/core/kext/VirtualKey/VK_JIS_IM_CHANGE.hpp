#ifndef VIRTUALKEY_VK_JIS_IM_CHANGE_HPP
#define VIRTUALKEY_VK_JIS_IM_CHANGE_HPP

#include "TimerWrapper.hpp"

namespace org_pqrs_KeyRemap4MacBook {
  namespace VirtualKey {
    class VK_JIS_IM_CHANGE {
    public:
      class SeesawType {
      public:
        enum Value {
          NONE,
          CUR_PRE,
          EISUU_KANA,
          KANA_OTHERS,
          KANA_EISUU,
          EISUU_OTHERS,
        };
      };

      class SkipType {
      public:
        enum Value {
          NONE,
          NONE_FORWARD,
          NONE_BACK,
          PRE_FORWARD,
          PRE_BACK,
          EISUU_KANA,
          KANA,
          EISUU,
        };
      };

      class ReplaceType {
      public:
        enum Value {
          NONE,
          NOSKIP,
          SKIP_PREVIOUS,
          SKIP_SPECIFIC,
        };
      };

      // This enum name may not be suitable.
      // I named it temporary.
      class SavedInputModeIndex {
      public:
        enum Value {
          NONE,
          ROMAN,
          HIRAGANA,
          KATAKANA,
          HALFWIDTH_KANA,
          AINU,
          FULLWIDTH_ROMAN,
          END_,
        };

        SavedInputModeIndex(void) : value_(NONE) {}

        Value get(void) const { return value_; }
        void set(Value newval) { if (newval != NONE) { value_ = newval; } }

        bool operator==(SavedInputModeIndex other) const { return value_ == other.get(); }
        bool operator!=(SavedInputModeIndex other) const { return ! (*this == other); }

        bool operator==(Value other) const { return value_ == other; }
        bool operator!=(Value other) const { return ! (*this == other); }

      private:
        Value value_;
      };

      // This enum name may not be suitable.
      // I named it temporary.
      class SavedInputModeType {
      public:
        enum Value {
          PREVIOUS,
          CURRENT,
          OTHERS,
          END_,
        };
      };

      class SignPlusMinus {
      public:
        enum Value {
          NONE,
          PLUS,
          MINUS,
        };
      };

      class CallbackType {
      public:
        enum Value {
          INIT,
          RESTORE,
          SEESAW_INIT,
        };
      };

      class StageType {
      public:
        enum Value {
          POST_REMAP,
          JUST_AFTER_REMAP,
          NON_REMAPPED,
        };
      };

      static void initialize(IOWorkLoop& workloop);
      static void terminate(void);

      static void scheduleCallback(CallbackType::Value callbacktype);
      static void cancelCallback(void);

      static void set_omit_initialize(bool omit_initialize) { omit_initialize_ = omit_initialize; }

      static void static_set_case1_pass_restore(int case1_pass_restore00);
      static int get_case1_pass_restore(void) { return case1_pass_restore2_; }

      static void ControlWorkspaceData(Params_KeyboardEventCallBack& params, StageType::Value stage);

      static void reverse_sign_CHANGE_SKIP(int when00);
      static const BridgeWorkSpaceData& getwsd_public(void) { return wsd_public_; }

      enum ControlWorkspaceDataType {
        CONTROL_WORKSPACEDATA_UPDATE,
        CONTROL_WORKSPACEDATA_LEARN,
        CONTROL_WORKSPACEDATA_REPLACE,
        CONTROL_WORKSPACEDATA_RESTORE,
      };

      static bool control_WSD(ControlWorkspaceDataType type, KeyCode modekey00, Flags flag00, InputModeDetail IMDsaved00);
      static bool update_WSD(void) {
        return control_WSD(CONTROL_WORKSPACEDATA_UPDATE, KeyCode::VK_NONE, ModifierFlag::NONE, InputModeDetail::UNKNOWN);
      };
      static bool learn_WSD(void) {
        return control_WSD(CONTROL_WORKSPACEDATA_LEARN, KeyCode::VK_NONE, ModifierFlag::NONE, InputModeDetail::UNKNOWN);
      };
      static bool replace_WSD(KeyCode modekey00, Flags flag00) {
        return control_WSD(CONTROL_WORKSPACEDATA_REPLACE, modekey00, flag00, InputModeDetail::UNKNOWN);
      };
      static bool restore_WSD(InputModeDetail IMDsaved00) {
        return control_WSD(CONTROL_WORKSPACEDATA_RESTORE, KeyCode::VK_NONE, ModifierFlag::NONE, IMDsaved00);
      };

      static bool handle(const Params_KeyboardEventCallBack& params);

    private:
      static void restore_timer_callback(OSObject* owner, IOTimerEventSource* sender);

      static SavedInputModeIndex::Value get_index_for_seesaw_AtoB_WSD(SeesawType::Value type);
      // XXX: DO NOT PASS int[] without length!!!
      static SavedInputModeIndex::Value get_index_for_replaceWSD(SignPlusMinus::Value sign00, bool skip[], ReplaceType::Value replacetype);

      static void set_new_index(SavedInputModeIndex::Value index);

      static KeyCode newkeycode_;
      static Flags newflag_;
      static TimerWrapper restore_timer_;
      static CallbackType::Value callbacktype_;

      static bool omit_initialize_;
      static int case1_pass_restore2_;

      static SavedInputModeIndex savedInputMode_[SavedInputModeType::END_];

      static SignPlusMinus::Value sign_plus_minus2_;
      static int counter_plus_minus2_;
      static int pre_counter_plus_minus2_;
      static bool seesaw_init2_;

      // XXX remove this value (replace by CommonData::current_workspacedata_)
      static BridgeWorkSpaceData wsd_public_;
      static BridgeWorkSpaceData wsd_save_[SavedInputModeIndex::END_];
      // XXX this value name may be wrong. (not wsd_learned_ but "bool initialized"?)
      static BridgeWorkSpaceData wsd_learned_;

      // XXX change function name
      static SavedInputModeIndex::Value IMD2index(InputModeDetail inputmodedetail);
      static SavedInputModeIndex::Value modeKey2index(KeyCode key, Flags flags);
    };
  }
}

#endif
