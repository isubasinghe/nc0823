(declare-fun node_Err_ok () Bool)
(declare-fun node_Err_ok__s_add_i_overflow () Bool)
(declare-fun node_Err_ok__i_add_1_overflow () Bool)
(declare-fun node_Err_ok__loop_inv_maintained () Bool)
(declare-fun node_Err_ok__loop_inv_established () Bool)
(declare-fun node_Ret_ok () Bool)
(declare-fun node_2_ok () Bool)
(declare-fun node_17_ok () Bool)
(declare-fun node_13_ok () Bool)
(declare-fun node_12_ok () Bool)
(declare-fun node_7_ok () Bool)
(declare-fun node_5_ok () Bool)
(declare-fun node_6_ok () Bool)
(declare-fun node_3_ok () Bool)
(declare-fun node_1_ok () Bool)
(declare-fun node_11_ok () Bool)
(declare-fun node_10_ok () Bool)
(declare-fun node_9_ok () Bool)
(declare-fun node_8_ok () Bool)
(declare-fun node_4_ok () Bool)

(declare-fun s___int@v~1 () (_ BitVec 32))
(declare-fun i___int@v~1 () (_ BitVec 32))
(declare-fun loop@4@count~1 () (_ BitVec 64))
(declare-fun s___int@v~2 () (_ BitVec 32))
(declare-fun i___int@v~2 () (_ BitVec 32))
(declare-fun loop@4@count~2 () (_ BitVec 64))
(declare-fun n___int@v~1 () (_ BitVec 32))
(declare-fun ret__int@v~1 () (_ BitVec 32))
(declare-fun s___int@v~3 () (_ BitVec 32))
(declare-fun i___int@v~3 () (_ BitVec 32))
(declare-fun loop@4@count~3 () (_ BitVec 64))

; loop invariant (i <= n && s == (i-1)*i/2)
(define-fun loop_invariant@5 ((loop@4@count (_ BitVec 64)) (i___int@v (_ BitVec 32)) (s___int@v (_ BitVec 32))) Bool (
    and (bvsle (_ bv0 32) i___int@v)
        (bvsle i___int@v n___int@v~1)
        (= s___int@v (
            bvsdiv (bvmul (bvsub i___int@v (_ bv1 32)) i___int@v)
                   (_ bv2 32))
        )
))

; pre condition (0 <= n && n <= 100)
(assert (and (bvslt (_ bv0 32) n___int@v~1) (bvslt n___int@v~1 (_ bv100 32))))

(assert (= node_Err_ok false))
(assert (= node_Err_ok__loop_inv_established false))
(assert (= node_Err_ok__loop_inv_maintained false))
(assert (= node_Err_ok__s_add_i_overflow false))
(assert (= node_Err_ok__i_add_1_overflow false))
(assert (= node_Ret_ok true))
(assert (= node_2_ok (and (=> false node_1_ok) (=> true node_Err_ok))))
(assert (= node_17_ok node_13_ok))
(assert (= node_13_ok (=> (= s___int@v~1 (_ bv0 32)) node_12_ok)))
(assert (= node_12_ok (=> (= i___int@v~1 (_ bv0 32)) node_7_ok)))
(assert (= node_7_ok (=> (= loop@4@count~1 (_ bv0 64)) (and node_5_ok (=> (not (loop_invariant@5 loop@4@count~1 i___int@v~1 s___int@v~1)) node_Err_ok__loop_inv_established)))))
(assert (= node_5_ok (=> (loop_invariant@5 loop@4@count~2 i___int@v~2 s___int@v~2) (and (=> true node_6_ok) (=> false node_Err_ok)))))
(assert (= node_6_ok (and (=> (bvslt i___int@v~2 n___int@v~1) node_11_ok) (=> (not (bvslt i___int@v~2 n___int@v~1)) node_3_ok))))
(assert (= node_3_ok (=> (= ret__int@v~1 s___int@v~2) node_1_ok)))
(assert (= node_1_ok node_Ret_ok))
(assert (= node_11_ok (and (=> (= (bvsle s___int@v~2 (bvadd s___int@v~2 i___int@v~2)) (bvsle (_ bv0 32) i___int@v~2)) node_10_ok) (=> (not (= (bvsle s___int@v~2 (bvadd s___int@v~2 i___int@v~2)) (bvsle (_ bv0 32) i___int@v~2))) node_Err_ok__s_add_i_overflow))))
(assert (= node_10_ok (=> (= s___int@v~3 (bvadd s___int@v~2 i___int@v~2)) node_9_ok)))
(assert (= node_9_ok (and (=> (= (bvsle i___int@v~2 (bvadd i___int@v~2 (_ bv1 32))) (bvsle (_ bv0 32) (_ bv1 32))) node_8_ok) (=> (not (= (bvsle i___int@v~2 (bvadd i___int@v~2 (_ bv1 32))) (bvsle (_ bv0 32) (_ bv1 32)))) node_Err_ok__i_add_1_overflow))))
(assert (= node_8_ok (=> (= i___int@v~3 (bvadd i___int@v~2 (_ bv1 32))) node_4_ok)))
(assert (= node_4_ok (=> (= loop@4@count~3 (bvadd loop@4@count~2 (_ bv1 64))) (=> (not (loop_invariant@5 loop@4@count~3 i___int@v~3 s___int@v~3)) node_Err_ok__loop_inv_maintained))))
(check-sat)
(assert (not node_17_ok))
(check-sat)
(get-model)
