try {
    throw 20;
    print(1);
} catch(e) {
    print(e);
    throw 30
} finally {
    print(2);
}