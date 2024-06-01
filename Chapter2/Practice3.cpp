//无限循环：unsigned integer在-1时自动转换成4294967275
int main() {
	for (unsigned int u = 10; u >= 0; --u)
		std::cout << u << std::endl;
}