// 排序算法中的比较器

int[] numbers = { 5, 2, 9, 1, 5, 6 };

// 使用委托定义比较逻辑
Comparison<int> comparer = (x, y) => x.CompareTo(y);
        
// 对数组进行排序
Array.Sort(numbers, comparer);

foreach (int number in numbers)
{
    Console.WriteLine(number);
}

// 异步操作示例 
AsyncOperation operation = new AsyncOperation();
operation.StartOperation(result =>
{
    if (result)
        Console.WriteLine("Operation completed successfully.");
    else
        Console.WriteLine("Operation failed.");
});

delegate void AsyncOperationCompletedHandler(bool success);
class AsyncOperation
{
    public void StartOperation(AsyncOperationCompletedHandler callback)
    {
        Thread.Sleep(2000); // 模拟耗时操作
        callback(true); // 调用回调函数
    }
}


