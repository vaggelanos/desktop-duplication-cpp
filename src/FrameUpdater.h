#pragma once
#include "stable.h"

#include "BaseRenderer.h"

#include <array>
#include <meta/comptr.h>
#include <vector>

struct FrameUpdate;
struct FrameContext;

struct RenderFailure {
    RenderFailure(HRESULT res, const char *text) noexcept {}
};

struct FrameUpdater {
    struct InitArgs : BaseRenderer::InitArgs {
        HANDLE targetHandle{}; // shared texture handle that should be updated
    };
    using Vertex = BaseRenderer::Vertex;
    using quad_vertices = std::array<Vertex, 6>;

    FrameUpdater(InitArgs &&args);

    void update(const FrameUpdate &data, const FrameContext &context);

private:
    void performMoves(const FrameUpdate &data, const FrameContext &context);
    void updateDirty(const FrameUpdate &data, const FrameContext &context);

private:
    struct Resources : BaseRenderer {
        Resources(FrameUpdater::InitArgs &&args);

        void prepare(HANDLE targetHandle);

        void activateRenderTarget() {
            deviceContext()->OMSetRenderTargets(1, renderTarget.GetAddressOf(), nullptr);
        }

        ComPtr<ID3D11Texture2D> target;
        ComPtr<ID3D11RenderTargetView> renderTarget;

        ComPtr<ID3D11Texture2D> moveTmp;
    };
    Resources m_dx;

    std::vector<quad_vertices> m_dirtyQuads;
};
