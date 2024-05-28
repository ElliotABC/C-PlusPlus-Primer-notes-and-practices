#include <iostream>
#include <vector>

// 命令接口
class Command
{
public:
    virtual ~Command()
    {
    }

    virtual void execute() const = 0;
};

// 具体命令类1
class ConcreteCommand1 : public Command
{
public:
    ConcreteCommand1()
    {
    }

    void execute() const override
    {
        std::cout << "Executing ConcreteCommand1" << std::endl;
    }
};

// 具体命令类2
class ConcreteCommand2 : public Command
{
public:
    ConcreteCommand2()
    {
    }

    void execute() const override
    {
        std::cout << "Executing ConcreteCommand2" << std::endl;
    }
};

class ConcreteCommand3 : public Command
{
public:
    ConcreteCommand3()
    {
        
    }

    void execute() const override
    {
        for (int i = 1; i <= 9; i++)
        {
            for (int j = 1; j <= i; j++)
            {
                std::cout << j << "*" << i << "=" << i * j << "\t";
            }
            std::cout << '\n';
        }
    }
};

// 请求者/调用者角色
class Invoker
{
private:
    std::vector<Command*> commands;

public:
    void addCommand(Command* cmd)
    {
        commands.push_back(cmd);
    }

    void executeCommands()
    {
        for (Command* cmd : commands)
        {
            cmd->execute();
        }
    }
};

int main()
{
    // 创建命令对象
    ConcreteCommand1 cmd1;
    ConcreteCommand2 cmd2;
    ConcreteCommand3 cmd3;
    
    // 创建请求者对象
    Invoker invoker;

    // 将命令添加到请求者
    invoker.addCommand(&cmd1);
    invoker.addCommand(&cmd2);
    invoker.addCommand(&cmd3);
    
    // 执行命令
    invoker.executeCommands();

    return 0;
}
