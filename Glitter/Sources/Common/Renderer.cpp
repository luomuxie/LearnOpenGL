// Renderer.cpp
#include <glad/glad.h>
#include <vector>
#include <iostream>

class Renderer {
public:
    struct FramebufferAttachment {
        enum class Type {
            Color,
            Depth,
            Stencil,
            DepthStencil
        } type;
        unsigned int textureID = 0;
        unsigned int rboID = 0;

        GLint minFilter = GL_LINEAR; // ������С������
        GLint magFilter = GL_LINEAR; // ����Ŵ������
        GLint wrapS = GL_CLAMP_TO_EDGE; // S�������װ��ʽ
        GLint wrapT = GL_CLAMP_TO_EDGE; // T�������װ��ʽ
        GLint internalFormat = GL_RGB; // �����ڲ���ʽ
        GLint format = GL_RGB; // Դͼ���ʽ
        GLenum dataType = GL_UNSIGNED_BYTE; // �����ֶΣ�����������������
    };

    unsigned int createFramebuffer(const std::vector<FramebufferAttachment>& attachments, int width, int height) {
        unsigned int fbo;
        glGenFramebuffers(1, &fbo);
        glBindFramebuffer(GL_FRAMEBUFFER, fbo);

        std::vector<GLenum> colorAttachments;
        for (auto& attachment : attachments) {
            if (attachment.type == FramebufferAttachment::Type::Color) {
                // ͨ������ֱ���޸�ԭʼ�����еĶ���
                attachment.textureID = createAndConfigureTexture(attachment, width, height);

                glFramebufferTexture2D(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + colorAttachments.size(), GL_TEXTURE_2D, attachment.textureID, 0);
                colorAttachments.push_back(GL_COLOR_ATTACHMENT0 + colorAttachments.size());
            }
            // �����������͵ĸ���...
        }

        if (!colorAttachments.empty()) {
            glDrawBuffers(static_cast<GLsizei>(colorAttachments.size()), colorAttachments.data());
        }

        if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
            std::cout << "ERROR::FRAMEBUFFER:: Framebuffer is not complete!" << std::endl;
        }

        glBindFramebuffer(GL_FRAMEBUFFER, 0);
        return fbo;
    }

    unsigned int createAndConfigureTexture(const FramebufferAttachment& attachment, int width, int height) {
        unsigned int textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, attachment.internalFormat, width, height, 0, attachment.format, attachment.dataType, nullptr);

        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, attachment.minFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, attachment.magFilter);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, attachment.wrapS);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, attachment.wrapT);

        glBindTexture(GL_TEXTURE_2D, 0); // Unbind the texture

        return textureID;
    }
};

int main() {
    // ��ʼ��OpenGL��GLFW��
    // ...

    Renderer renderer;
    std::vector<Renderer::FramebufferAttachment> attachments = {
        // ��ʼ��attachments
    };
    //unsigned int fbo = renderer.createFramebuffer(attachments);

    // ʹ��FBO������Ⱦ��
    // ...

    return 0;
}
