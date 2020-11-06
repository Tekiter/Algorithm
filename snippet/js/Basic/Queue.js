const Queue = (function () {
  const q = function () {
    this.inStk = [];
    this.outStk = [];
  };

  const normalize = function (queue) {
    if (queue.outStk.length === 0) {
      while (queue.inStk.length) {
        queue.outStk.push(queue.inStk.pop());
      }
    }
  };

  q.prototype.push = function (item) {
    this.inStk.push(item);
  };

  q.prototype.pop = function () {
    normalize(this);
    if (this.outStk.length === 0) {
      throw new RangeError("No items in queue");
    }
    return this.outStk.pop();
  };

  q.prototype.front = function () {
    normalize(this);
    if (this.outStk.length === 0) {
      throw new RangeError("No items in queue");
    }
    return this.outStk[this.outStk.length - 1];
  };

  q.prototype.size = function () {
    return this.inStk.length + this.outStk.length;
  };

  q.prototype.toString = function () {
    return "[" + [...this] + "]";
  };

  q.prototype[Symbol.iterator] = function* () {
    for (let i in this.outStk) {
      yield this.outStk[this.outStk.length - 1 - i];
    }
    for (let i in this.inStk) {
      yield this.inStk[i];
    }
  };

  return q;
})();

// Usage
function test() {
  const q = new Queue();

  // Enqueue
  q.push(3);
  q.push(5);
  q.push(7);

  // Dequeue
  console.log(q.pop());

  // Peek
  console.log(q.front());

  // Size
  q.push(10);
  console.log(q.size());

  // Iterate
  for (let v of q) {
    console.log(v);
  }

  // To Array
  console.log([...q]);

  // To String
  console.log(q + "");
}

// Output
// 3
// 5
// 3
// 5
// 7
// 10
// [5, 7, 10]
// [5,7,10]
