int main()
{
    ThreadPool pool(4);
    auto task = pool.exec([]() { return 0; });
    auto ret = task.get();
    std::cout << ret << std::endl;
    return 0;
}
