function Array_indexOf(obj, index) { 
    var i = index || 0;
    var iz = this.length;

    i = (i < 0) ? i + iz : i;
    for (; i < iz; ++i) {
        if (this[i] === obj) {
            return i;
        }
    }
    return -1;
}

Array.prototype.indexOf = Array_indexOf;