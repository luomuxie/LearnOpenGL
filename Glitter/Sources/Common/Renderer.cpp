
#ifndef RENDERER_H  
#define RENDERER_H  

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
            DepthStencil
        } type;
        unsigned int textureID = 0;        

        GLint minFilter = GL_LINEAR; // ������С������
        GLint magFilter = GL_LINEAR; // ����Ŵ������
        GLint wrapS = GL_CLAMP_TO_EDGE; // S�������װ��ʽ
        GLint wrapT = GL_CLAMP_TO_EDGE; // T�������װ��ʽ
        GLint internalFormat = GL_RGB; // �����ڲ���ʽ
        GLint format = GL_RGB; // Դͼ���ʽ
        GLenum dataType = GL_UNSIGNED_BYTE; // �����ֶΣ�����������������

        FramebufferAttachment(Type type,
            GLint internalFormat = GL_RGB,
            GLint format = GL_RGB,
            GLenum dataType = GL_UNSIGNED_BYTE,
            GLint minFilter = GL_LINEAR,
            GLint magFilter = GL_LINEAR,
            GLint wrapS = GL_CLAMP_TO_EDGE,
            GLint wrapT = GL_CLAMP_TO_EDGE)
            : type(type), internalFormat(internalFormat), format(format), dataType(dataType),
            minFilter(minFilter), magFilter(magFilter), wrapS(wrapS), wrapT(wrapT) {
            // �������ͽ��и����ʼ��������
        }

    };

    unsigned static int createFramebuffer(std::vector<FramebufferAttachment>& attachments, int width, int height) {
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
            else if (attachment.type == FramebufferAttachment::Type::Depth) {
				glGenRenderbuffers(1, &fbo);
				glBindRenderbuffer(GL_RENDERBUFFER, fbo);
				glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH_COMPONENT, width, height);
				glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_ATTACHMENT, GL_RENDERBUFFER, fbo);
			}            
            else if (attachment.type == FramebufferAttachment::Type::DepthStencil) {
				// �������ģ�建�帽��...                                            
                glGenRenderbuffers(1, &fbo);
                glBindRenderbuffer(GL_RENDERBUFFER, fbo);
                glRenderbufferStorage(GL_RENDERBUFFER, GL_DEPTH24_STENCIL8, width, height);
                glBindRenderbuffer(GL_RENDERBUFFER, 0);
                // ��RBO���ӵ�FBO
                glFramebufferRenderbuffer(GL_FRAMEBUFFER, GL_DEPTH_STENCIL_ATTACHMENT, GL_RENDERBUFFER, fbo);
			}
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

    unsigned static int createAndConfigureTexture(const FramebufferAttachment& attachment, int width, int height) {
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
#endif
