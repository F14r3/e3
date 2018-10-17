template<> void $NameUint<2>::d_add
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n6 = gate_nand(b[0], a[0]);
    auto n5 = gate_xor(b[1], a[1]);
    y[1] = gate_xnor(n6, n5);
    y[0] = gate_xor(b[0], a[0]);
}


template<> void $NameUint<2>::d_and
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    y[1] = gate_and(b[1], a[1]);
    y[0] = gate_and(b[0], a[0]);
}


template<> void $NameUint<2>::d_bmul
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    y[1] = gate_and(a[0], b[1]);
    y[0] = gate_and(a[0], b[0]);
}


template<> void $NameUint<2>::d_bmux
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b, const vector<Bit> & c) noexcept
{
    y[0] = gate_mux(a[0], b[0], c[0]);
    y[1] = gate_mux(a[0], b[1], c[1]);
}


template<> void $NameUint<2>::d_div
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n3 = gate_not(a[0]);
    auto n5 = gate_nand(b[0], n3);
    auto n6 = gate_not(a[1]);
    auto n4 = gate_nand(b[1], n6);
    y[0] = gate_and(n5, n4);
    auto n8 = gate_not(b[1]);
    auto n7 = gate_nand(b[0], n6);
    y[1] = gate_and(n8, n7);
}


template<> void $NameUint<2>::d_eq
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n8 = gate_not(a[0]);
    auto n11 = gate_xor(n8, b[0]);
    auto n9 = gate_not(b[1]);
    auto n10 = gate_xor(n9, a[1]);
    y[0] = gate_and(n11, n10);
}


template<> void $NameUint<2>::d_ge
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n8 = gate_not(b[1]);
    auto n13 = gate_nand(n8, a[1]);
    auto n11 = gate_xor(n8, a[1]);
    auto n9 = gate_not(a[0]);
    auto n10 = gate_nand(b[0], n9);
    auto n12 = gate_nand(n11, n10);
    y[0] = gate_nand(n13, n12);
}


template<> void $NameUint<2>::d_gt
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n10 = gate_not(a[1]);
    auto n15 = gate_nand(n10, b[1]);
    auto n13 = gate_xor(n10, b[1]);
    auto n11 = gate_not(b[0]);
    auto n12 = gate_nand(a[0], n11);
    auto n14 = gate_nand(n13, n12);
    y[0] = gate_and(n15, n14);
}


template<> void $NameUint<2>::d_ineq
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n5 = gate_not(a[0]);
    auto n8 = gate_xor(n5, b[0]);
    auto n6 = gate_not(a[1]);
    auto n7 = gate_xor(n6, b[1]);
    y[0] = gate_nand(n8, n7);
}


template<> void $NameUint<2>::d_land
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n10 = gate_not(b[0]);
    auto n9 = gate_not(b[1]);
    auto n14 = gate_nand(n10, n9);
    auto n12 = gate_not(a[0]);
    auto n11 = gate_not(a[1]);
    auto n13 = gate_nand(n12, n11);
    y[0] = gate_and(n14, n13);
}


template<> void $NameUint<2>::d_le
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n7 = gate_not(a[1]);
    auto n12 = gate_nand(n7, b[1]);
    auto n10 = gate_xor(n7, b[1]);
    auto n8 = gate_not(b[0]);
    auto n9 = gate_nand(a[0], n8);
    auto n11 = gate_nand(n10, n9);
    y[0] = gate_nand(n12, n11);
}


template<> void $NameUint<2>::d_lnot
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    auto n7 = gate_not(a[0]);
    auto n6 = gate_not(a[1]);
    y[0] = gate_and(n7, n6);
}


template<> void $NameUint<2>::d_lor
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n12 = gate_not(a[1]);
    auto n11 = gate_not(b[1]);
    auto n10 = gate_and(n12, n11);
    auto n14 = gate_not(b[0]);
    auto n13 = gate_not(a[0]);
    auto n9 = gate_and(n14, n13);
    y[0] = gate_nand(n10, n9);
}


template<> void $NameUint<2>::d_lt
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n9 = gate_not(b[1]);
    auto n14 = gate_nand(n9, a[1]);
    auto n12 = gate_xor(n9, a[1]);
    auto n10 = gate_not(a[0]);
    auto n11 = gate_nand(b[0], n10);
    auto n13 = gate_nand(n12, n11);
    y[0] = gate_and(n14, n13);
}


template<> void $NameUint<2>::d_mm
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[0] = gate_not(a[0]);
    y[1] = gate_xor(a[1], y[0]);
}


template<> void $NameUint<2>::d_mod
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n3 = gate_not(a[1]);
    auto n4 = gate_nand(b[1], n3);
    auto n5 = gate_nand(n4, b[0]);
    y[0] = gate_and(a[0], n5);
    auto n6 = gate_not(a[0]);
    auto n7 = gate_nand(b[1], n6);
    auto n8 = gate_mux(b[0], n7, b[1]);
    auto n9 = gate_not(n8);
    y[1] = gate_and(a[1], n9);
}


template<> void $NameUint<2>::d_mul
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    y[0] = gate_and(a[0], b[0]);
    auto n6 = gate_nand(a[1], b[0]);
    auto n5 = gate_nand(b[1], a[0]);
    y[1] = gate_xor(n6, n5);
}


template<> void $NameUint<2>::d_mux
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b, const vector<Bit> & c) noexcept
{
    auto n5 = gate_not(a[0]);
    auto n4 = gate_not(a[1]);
    auto n6 = gate_nand(n5, n4);
    y[0] = gate_mux(n6, b[0], c[0]);
    y[1] = gate_mux(n6, b[1], c[1]);
}


template<> void $NameUint<2>::d_not
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[1] = gate_not(a[1]);
    y[0] = gate_not(a[0]);
}


template<> void $NameUint<2>::d_or
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n6 = gate_not(b[1]);
    auto n5 = gate_not(a[1]);
    y[1] = gate_nand(n6, n5);
    auto n8 = gate_not(b[0]);
    auto n7 = gate_not(a[0]);
    y[0] = gate_nand(n8, n7);
}


template<> void $NameUint<2>::d_pp
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[1] = gate_xor(a[0], a[1]);
    y[0] = gate_not(a[0]);
}


template<> void $NameUint<2>::d_redand
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[0] = gate_and(a[0], a[1]);
}


template<> void $NameUint<2>::d_rednand
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[0] = gate_nand(a[0], a[1]);
}


template<> void $NameUint<2>::d_rednor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    auto n7 = gate_not(a[0]);
    auto n6 = gate_not(a[1]);
    y[0] = gate_and(n7, n6);
}


template<> void $NameUint<2>::d_redor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    auto n4 = gate_not(a[0]);
    auto n3 = gate_not(a[1]);
    y[0] = gate_nand(n4, n3);
}


template<> void $NameUint<2>::d_redxnor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[0] = gate_xnor(a[0], a[1]);
}


template<> void $NameUint<2>::d_redxor
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[0] = gate_xor(a[0], a[1]);
}


template<> void $NameUint<2>::d_sll
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n11 = gate_not(b[0]);
    auto n10 = gate_and(a[0], n11);
    auto n13 = gate_not(b[1]);
    y[0] = gate_and(n10, n13);
    auto n12 = gate_mux(b[0], a[0], a[1]);
    y[1] = gate_and(n13, n12);
}


template<> void $NameUint<2>::d_slr
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    auto n11 = gate_not(b[0]);
    auto n10 = gate_and(a[1], n11);
    auto n13 = gate_not(b[1]);
    y[1] = gate_and(n10, n13);
    auto n12 = gate_mux(b[0], a[1], a[0]);
    y[0] = gate_and(n13, n12);
}


template<> void $NameUint<2>::d_sub
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    y[0] = gate_xor(a[0], b[0]);
    auto n8 = gate_not(b[1]);
    auto n5 = gate_not(a[0]);
    auto n6 = gate_nand(b[0], n5);
    auto n7 = gate_xor(n6, a[1]);
    y[1] = gate_xor(n8, n7);
}


template<> void $NameUint<2>::d_uminus
(vector<Bit> & y, const vector<Bit> & a) noexcept
{
    y[0] = a[0];
    y[1] = gate_xor(a[0], a[1]);
}


template<> void $NameUint<2>::d_xor
(vector<Bit> & y, const vector<Bit> & a, const vector<Bit> & b) noexcept
{
    y[1] = gate_xor(b[1], a[1]);
    y[0] = gate_xor(b[0], a[0]);
}

