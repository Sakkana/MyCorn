#include "transform_to_image.h"

TransformToImage::TransformToImage(std::vector<Mesh> meshes)
{
    this->m_meshes = meshes;

    int meshes_size = meshes.size();
    this->m_max_coord.resize(meshes_size);
    this->m_min_coord.resize(meshes_size);

    // 初始化每个网格的包围盒初值
    for (int mesh_idx = 0; mesh_idx < meshes_size; ++ mesh_idx)
    {
        for (int i = 0; i < VERTEX_NUM; ++i)
        {
            this->m_max_coord[mesh_idx].push_back(-INF);
            this->m_max_coord[mesh_idx].push_back(-INF);
            this->m_max_coord[mesh_idx].push_back(-INF);

            this->m_min_coord[mesh_idx].push_back(INF);
            this->m_min_coord[mesh_idx].push_back(INF);
            this->m_min_coord[mesh_idx].push_back(INF);
        }
    }

    LOG_TEXT("initialization succeed");
}

void TransformToImage::transform()
{
    // 计算三维包围盒
    this->get_bounding_box();

    // 二维映射
    this->mapping();
}

void TransformToImage::get_bounding_box()
{
    // 保存该点坐标的临时变量
    std::vector<float> points(3);

    int mesh_num = this->m_meshes.size();
    LOG_VARIABLE("mesh_num", mesh_num);
    std::cout << m_meshes[0].vertices[0].Position.x << " " << m_meshes[0].vertices[0].Position.y << " " << m_meshes[0].vertices[0].Position.z << std::endl;

    for (int mesh_idx = 0; mesh_idx < mesh_num; ++mesh_idx)
    {
        // 当前 mesh 中顶点的数量
        int cur_mesh_size = m_meshes[mesh_idx].vertices.size();
        LOG_VARIABLE("vertices in mesh bounding box", cur_mesh_size);

        // 获取每一行顶点坐标
        for (int vertex_idx = 0; vertex_idx < cur_mesh_size; ++vertex_idx)
        {
            points[0] = this->m_meshes[mesh_idx].vertices[vertex_idx].Position.x;
            points[1] = this->m_meshes[mesh_idx].vertices[vertex_idx].Position.y;
            points[2] = this->m_meshes[mesh_idx].vertices[vertex_idx].Position.z;

            for (int i = 0; i < VERTEX_NUM; ++i)
            {

                // 获取包围盒参数
                m_max_coord[mesh_idx][i] = std::max(m_max_coord[mesh_idx][i], points[i]);
                m_min_coord[mesh_idx][i] = std::min(m_min_coord[mesh_idx][i], points[i]);
            }

            // 坐标系的 y, z 在 obj 里是相反的
            std::swap(points[1], points[2]);
        }
    }

}

void TransformToImage::mapping()
{
    // 保存该点坐标的临时变量
    std::vector<float> points(3);

    int mesh_num = this->m_meshes.size();
    LOG_VARIABLE("mesh_num", mesh_num);

    for (int mesh_idx = 0; mesh_idx < mesh_num; ++mesh_idx)
    {
        // 当前 mesh 中顶点的数量
        int cur_mesh_size = m_meshes[mesh_idx].vertices.size();
        LOG_VARIABLE("vertices in mesh mapping", cur_mesh_size);

        // 获取每一行顶点坐标
        for (int vertex_idx = 0; vertex_idx < cur_mesh_size; ++vertex_idx)
        {
            points[0] = this->m_meshes[mesh_idx].vertices[vertex_idx].Position.x;
            points[1] = this->m_meshes[mesh_idx].vertices[vertex_idx].Position.y;
            points[2] = this->m_meshes[mesh_idx].vertices[vertex_idx].Position.z;

            // 对 x, y, z 进行标准化
            for (int i = 0; i < VERTEX_NUM; ++i)
            {
                // normalization
                points[i] -= (m_max_coord[mesh_idx][i] + m_min_coord[mesh_idx][i]) / 2.0f;      // 平移到中心点
                points[i] /= m_max_coord[mesh_idx][i] - m_min_coord[mesh_idx][i];
            }

            // 坐标系的 y, z 在 obj 里是相反的
            std::swap(points[1], points[2]);

            // 做二维映射
            for (int i = 0; i < VERTEX_NUM; ++i)
            {
                if (i == 0)
                {
                    points[i] = (PI + std::atan2(points[2], points[0])) / (static_cast<float>(PI) * 2);
                    this->m_meshes[mesh_idx].vertices[vertex_idx].Position.x = points[i];
                }
                else if (i == 1)
                {
                    points[i] = (1 + points[1]) / 2;
                    this->m_meshes[mesh_idx].vertices[vertex_idx].Position.y = points[i];
                }
                else
                {
                    points[i] = 1.0;
                    this->m_meshes[mesh_idx].vertices[vertex_idx].Position.z = points[i];
                }

            }
        }


    }

    

}