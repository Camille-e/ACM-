template <typename Info>
struct SegmentTree {
    int n, size;
    vector<Info> info;
     SegmentTree(int n) : n(n) {
        size = 1;
        while (size <= n) {
            size <<= 1;
        }
        info.assign(size << 1, Info());
    }

    void pushup(int id) {
        info[id] = info[id << 1] + info[id << 1 | 1];
    }

    void update(int pos, const Info &val) {
        update(pos, val, 0, n - 1);
    }

    void update(int pos, const Info &val, int l, int r) {
        int id = pos + size;
        info[id] = val;
        for (id >>= 1; id; id >>= 1) {
            pushup(id);
        }
    }

    Info query(int pos) {
        return info[pos + size];
    }

    Info rangeQuery(int l, int r) {
        Info resl, resr;

        int x = l + size;
        int y = r + size;

        while (x <= y) {
            if (x & 1) {
                resl = resl + info[x++];
            }
            if (!(y & 1)) {
                resr = info[y--] + resr;
            }
            x >>= 1;
            y >>= 1;
        }

        return resl + resr;
    }
};
struct Info {
    int mn = 3e5;
};
Info operator+(const Info &x, const Info &y) {
    Info res;
    res.mn = min(x.mn, y.mn);
    return res;
}