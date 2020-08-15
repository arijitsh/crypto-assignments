def permutation(lst):
    # print(lst)
    if len(lst) == 1:
        return lst
    res = []
    for i in range(len(lst)):
        remaining = lst[:i] + lst[i+1:]
        p = permutation(remaining)
        for items in p:
            x_p = [lst[i]] + [items]
            # print(x_p)
            res.append(x_p)
    # print(lst)
    return res

if __name__ == "__main__":
    n = int(input("Enter n : "))
    assert(n > 0)
    nat_n = list(range(n+1))[1:]
    print(permutation(nat_n))
