from enum import Enum, unique


@unique
class Provenance(Enum):
    GRAPHLANG = "GRAPHLANG"
    NIP_GUARD = "NIP_GUARD"
    NIP_UPDATE = "NIP_UPDATE"
    DSA_JOINER = "DSA_JOINER"
    PRE_COND_FN_OBLIGATION = "PRE_COND_FN_OBLIGATION"
    POST_COND_FN_ASSUME = "POST_COND_FN_ASSUME"
    PRE_COND = "PRE_COND"
    POST_COND = "POST_COND"
    LOOP_INV_ASSUME = "LOOP_INV_ASSUME"
    LOOP_INV_OBLIGATION = "LOOP_INV_OBLIGATION"
    CALL_STASH_INITIAL_ARGS = "CALL_STASH_INITIAL_ARGS"
    CALL_STASH = "CALL_STASH"
    NODE_EMPTY = "NODE_EMPTY"

    LOOP_ITER_PRE = "LOOP_ITER_PRE"
    LOOP_ITER_POST = "LOOP_ITER_POST"