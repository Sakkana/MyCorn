# MyCorn

project structure:
##### class: Shader
##### class: Camera
- [x] 待解决：增加鼠标拖拽改变欧拉角的交互
- [ ] 增强拖拽的真实感, 操作更细腻
- [ ] 修复鼠标缩放响应消失问题
##### class: Model
##### class: Mesh
##### class: TransformToImage
- [x] 待解决：增加一个成员函数将渲染后的 2D Image 存储在 Framebuffer 中，
      并设计好接口将 buffer 的地址返回给 opcnCV 端读取
- [ ] 同时使用两个 opcnGL 上下文渲染 3D 和 2D 模型, 不使用 framebuffer 再用 openCV 的接口显示
##### main.cpp
- [ ] 修复矩阵, 解决玉米消失/一闪而过问题
- [ ] 修复表面渲染出来全是三角形面片问题（可能是法向量问题？）
