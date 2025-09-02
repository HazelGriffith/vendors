%-----Model Axioms

%-----IDLE STATE
%-----When is next state RM?
fof(when_is_next_state_RM,axiom,
      (ext(i,rm) => next(rm))).

%-----When does I externally transition to RM?
fof(ext_I_to_RM,axiom,
    curr(i)&rcvd(cr) => ext(i,rm) ).

%-----When is next state SP?
fof(when_is_next_state_SP,axiom,
      (ext(i,sp) => next(sp))).

%-----When does I externally transition to SP?
fof(ext_I_to_SP,axiom,
    curr(i)&(rcvd(vr1)|rcvd(vr2)) => ext(i,sp) ).

%-----REQUESTING MONEY STATE
%-----When is next state CM?
fof(when_is_next_state_CM,axiom,
     (ext(rm,cm) => next(cm)) ).

%-----When does RM externally transition to CM?
fof(ext_RM_to_CM,axiom,
     curr(rm)&rcvd(mi) => ext(rm,cm) ).

%-----CHECKING MONEY STATE
%-----When is next state RM?
fof(when_is_next_state_RM,axiom,
      int(cm,rm) => next(rm) ).

%-----When does CM internally transition to RM?
fof(int_CM_to_RM,axiom,
      curr(cm) & ta(cm) & mr < cost => int(cm,rm) ).

%-----When is next state V?
fof(when_is_next_state_V,axiom,
      int(cm,v) => next(v) ).

%-----When does CM internally transition to V?
fof(int_CM_to_V,axiom,
      curr(cm) & ta(cm) & mr < cost => int(cm,v) ).

%-----VENDING STATE
%-----When is next state CS?
fof(when_is_next_state_CS,axiom,
      int(v,cs) => next(cs) ).

%-----When does V internally transition to CS?
fof(int_V_to_CS,axiom,
      curr(v) & ta(v) & stock > 0 => int(v,cs) ).

%-----CHECKING STOCK STATE
%-----When is next state I?
fof(when_is_next_state_I,axiom,
      int(cs,i) => next(i) ).

%-----When does CS internally transition to I?
fof(int_CS_to_I,axiom,
       curr(cs)&ta(cs) => int(cs,i) ).

%-----SENDING PRODUCT STATE
%-----When is the next state CS?
fof(when_is_next_state_CS,axiom,
      int(sp,cs)=>next(cs) ).

%-----When does SP internally transition to CS?
fof(int_SP_to_CS,axiom,
      curr(sp) & ta(sp) & stock > 0 => int(sp,cs) ).