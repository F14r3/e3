// === BEGIN mod.pilx.h Name0=$Name0 Name1=$Name1

inline $Name1 to_$Name1(const $Name0Bool & c) { return $Name1(c[0].native()); }
inline $Name1 operator*(const $Name1 & m, const $Name0Bool & c) { return m * to_$Name1(c);}
inline $Name1 operator*(const $Name0Bool & c, const $Name1 & m) { return m * c; }

// === END mod.pilx.h Name0=$Name0 Name1=$Name1
