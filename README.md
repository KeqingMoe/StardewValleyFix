## StardewValleyFix

自动修复星露谷联机 bug **这个角色属于另一位玩家** 

### 运行环境

- Windows
- 64 位
- MacOS

### 使用方法

联机使用自己的角色出现 **这个角色属于另一位玩家** 提示后，让主机关闭存档，运行 `StardewValleyFix.exe` ，出现一闪而过的黑色窗口后，再打开存档。

### 手动编译

```
xmake
```

或自行整理成单个 `.cpp` 文件再编译。

#### MacOS使用方法

1. 在终端运行
```
brew install xmake
```

2. 编译运行
```
xmake run 
```


### 基本原理

把存档文件中的 `<userID>1145141919810</userID>` （类似这样，数字可能不同） 替换成 `<userID />`。

手动修复的操作细节详见我的博客上的 [这篇文章](https://keqing.moe/posts/stardew-valley-multiplay-bug-fix/)。

### 补充说明

不要运行多次这个软件，因为它会把旧存档备份一份，并加上 `.bak` 后缀。假如软件出现 bug 还能恢复备份文件，再[手动修复](https://keqing.moe/posts/stardew-valley-multiplay-bug-fix/)。运行多次会覆盖掉备份文件。
