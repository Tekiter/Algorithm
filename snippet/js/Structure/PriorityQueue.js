const PriorityQueue = (function () {
  const pq = function (compareFn) {
    if (compareFn) {
      this.compareFn = compareFn;
    }

    this.heap = [null];
  };

  const swap = function (pq, i, j) {
    const tmp = pq.heap[i];
    pq.heap[i] = pq.heap[j];
    pq.heap[j] = tmp;
  };

  pq.prototype.push = function (item) {
    this.heap.push(item);

    let cur = this.size();

    while (cur > 1) {
      const parent = cur >> 1;

      if (this.compareFn(this.heap[parent], this.heap[cur]) < 0) {
        swap(this, cur, parent);
        cur = parent;
      } else break;
    }
  };

  pq.prototype.pop = function () {
    const ret = this.top();

    if (this.size() === 1) {
      this.heap.pop();
      return ret;
    }

    this.heap[1] = this.heap.pop();

    let cur = 1;

    while (true) {
      let child = cur * 2;
      if (child > this.size()) {
        break;
      }

      if (
        child <= this.size() &&
        this.compareFn(this.heap[cur * 2], this.heap[cur * 2 + 1]) < 0
      ) {
        child++;
      }

      if (this.compareFn(this.heap[cur], this.heap[child]) >= 0) {
        break;
      }

      swap(this, cur, child);
      cur = child;
    }

    return ret;
  };

  pq.prototype.top = function () {
    if (this.size() === 0) {
      throw new RangeError("Cannot pq.top(). No items in queue.");
    }
    return this.heap[1];
  };

  pq.prototype.size = function () {
    return this.heap.length - 1;
  };

  return pq;
})();


// Usage
function test() {

    //
    // Int as item
    let pq = new PriorityQueue((a,b) => {return a-b});

    pq.push(5)
    pq.push(3)
    pq.push(4)
    pq.push(2)
    console.log(pq.pop())

    // OUTPUT
    // 5

    //
    // Array as item
    pq = new PriorityQueue((a,b) => {console.log(b) ; return a[0] - b[0]});
    
    // push
    pq.push([1,'a'])
    pq.push([5,'b'])
    pq.push([3,'c'])

    pq.push([2, 'd'])
    pq.push([4, 'e'])

    // top
    console.log('pq.top() : ' + pq.top())

    // pop
    console.log('pq.pop() : ' + pq.pop())
    console.log('pq.pop() : ' + pq.pop())
    console.log('pq.pop() : ' + pq.pop())

    console.log('pq.size() : ' + pq.size())

    // OUTPUT
    // pq.top() : 5,b
    // pq.pop() : 5,b
    // pq.pop() : 4,e
    // pq.pop() : 3,c
    // pq.size() : 2
}

test()