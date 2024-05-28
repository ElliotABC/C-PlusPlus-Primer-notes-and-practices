#include <iostream>
#include <string>
#include <vector>
#include <stack>

// 编辑器类
class Editor
{
public:
    void open(const std::string& fileName)
    {
        std::cout << "File " << fileName << " opened." << std::endl;
    }

    void save()
    {
        std::cout << "File saved." << std::endl;
    }

    void close()
    {
        std::cout << "File closed." << std::endl;
    }
};

// 命令接口
class EditorCommand
{
public:
    EditorCommand(Editor* editor) : editor(editor)
    {
    }

    virtual ~EditorCommand()
    {
    }

    virtual void execute() = 0;
    virtual void undo() = 0;

protected:
    Editor* editor;
};

// 具体命令类 - 打开文件
class OpenFileCommand : public EditorCommand
{
public:
    OpenFileCommand(Editor* editor, const std::string& fileName)
        : EditorCommand(editor), fileName(fileName)
    {
    }

    void execute() override
    {
        if (editor)
        {
            std::cout << "Opening file: " << fileName << std::endl;
            editor->open(fileName);
            history.push(fileName);
        }
    }

    void undo() override
    {
        if (!history.empty())
        {
            std::cout << "Closing file: " << fileName << std::endl;
            editor->close();
            history.pop();
        }
    }

private:
    std::string fileName;
    std::stack<std::string> history;
};

// 具体命令类 - 保存文件
class SaveFileCommand : public EditorCommand
{
public:
    SaveFileCommand(Editor* editor) : EditorCommand(editor)
    {
    }

    void execute() override
    {
        if (editor)
        {
            std::cout << "Saving file" << std::endl;
            editor->save();
        }
    }

    void undo() override
    {
        std::cout << "Undo not supported for Save operation." << std::endl;
    }
};

class Invoker
{
private:
    std::vector<EditorCommand*> commands;

public:
    void addCommand(EditorCommand* cmd)
    {
        commands.push_back(cmd);
    }

    void executeCommands()
    {
        for (EditorCommand* cmd : commands)
        {
            cmd->execute();
        }
    }

    void undoCommands()
    {
        for (auto it = commands.rbegin(); it != commands.rend(); ++it)
        {
            (*it)->undo();
        }
    }
};

int main()
{
    Editor editor;
    Invoker invoker;

    // 创建命令对象
    OpenFileCommand openCmd(&editor, "document.txt");
    SaveFileCommand saveCmd(&editor);

    // 添加命令到请求者
    invoker.addCommand(&openCmd);
    invoker.addCommand(&saveCmd);

    // 执行命令
    invoker.executeCommands();

    // 模拟撤销操作
    std::cout << "\nUndo operations:" << '\n';
    invoker.undoCommands();

    return 0;
}
