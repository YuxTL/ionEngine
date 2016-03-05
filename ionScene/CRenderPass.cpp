
#include "CRenderPass.h"


namespace ion
{
	namespace Scene
	{

		CRenderPass::CRenderPass(Graphics::IGraphicsAPI * GraphicsAPI, SharedPtr<Graphics::IGraphicsContext> GraphicsContext)
		{
			this->GraphicsAPI = GraphicsAPI;
			this->GraphicsContext = GraphicsContext;
		}

		void CRenderPass::SetRenderTarget(SharedPtr<Graphics::IRenderTarget> RenderTarget)
		{
			this->RenderTarget = RenderTarget;
		}

		string const & CRenderPass::GetName() const
		{
			return Name;
		}

		Graphics::IGraphicsAPI * CRenderPass::GetGraphicsAPI()
		{
			return GraphicsAPI;
		}

		SharedPtr<Graphics::IGraphicsContext> CRenderPass::GetGraphicsContext()
		{
			return GraphicsContext;
		}

		ICamera * CRenderPass::GetActiveCamera()
		{
			return ActiveCamera;
		}

		ICamera const * CRenderPass::GetActiveCamera() const
		{
			return ActiveCamera;
		}

		void CRenderPass::SetActiveCamera(ICamera * Camera)
		{
			ActiveCamera = Camera;
		}

		void CRenderPass::AddLight(ILight * Light)
		{
			Lights.insert(Light);
			RebuildLightUniformMatrix();
		}

		//void CRenderPass::RemoveLight(ILight * Light)
		//{
		//	Lights.erase(Light);
		//	RebuildLightUniformMatrix();
		//}

		void CRenderPass::AddSceneObject(ISceneObject * SceneObject)
		{
			SceneObjects.insert(SceneObject);
		}

		void CRenderPass::RemoveSceneObject(ISceneObject * SceneObject)
		{
			SceneObjects.erase(SceneObject);
		}

		void CRenderPass::Load()
		{
			if (ActiveCamera)
			{
				ActiveCamera->Update();

				*uViewMatrix = ActiveCamera->GetViewMatrix();
				*uProjectionMatrix = ActiveCamera->GetProjectionMatrix();
				*uCameraPosition = ActiveCamera->GetPosition();
			}

			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (! SceneObject->IsLoaded())
				{
					SceneObject->Load(this);
				}
			});
		}

		void CRenderPass::Draw()
		{
			std::for_each(SceneObjects.begin(), SceneObjects.end(), [this](ISceneObject * SceneObject)
			{
				if (SceneObject->IsVisible())
				{
					SceneObject->Draw(this);
				}
			});

			for (auto & Category : RenderQueue)
			{
				for (auto & Element : Category)
				{
					ISceneObject * SceneObject = std::get<0>(Element);
					SharedPtr<Graphics::IPipelineState> PipelineState = std::get<1>(Element);
					uint const InstanceCount = std::get<2>(Element);

					*uModelMatrix = SceneObject->GetTransformation();
					*uNormalMatrix = glm::inverse(glm::transpose(uModelMatrix->Value));

					if (1 == InstanceCount)
					{
						GraphicsContext->Draw(PipelineState);
					}
					else
					{
						GraphicsContext->DrawInstanced(PipelineState, InstanceCount);
					}
				}

				Category.clear();
			}
		}

		bool IsUniformNameArrayElement(string const & Label, int & Index, string & LHS, string & Remaining)
		{
			size_t OpenBrace = Label.find('['), CloseBrace = Label.find(']');
			if (OpenBrace != string::npos && CloseBrace != string::npos && OpenBrace + 1 < CloseBrace)
			{
				LHS = Label.substr(0, OpenBrace);
				Remaining = Label.substr(CloseBrace + 1);
				string const IndexString = Label.substr(OpenBrace + 1, CloseBrace - OpenBrace - 1);
				Index = std::stoi(IndexString);
				return true;
			}
			else
			{
				return false;
			}
		}

		void CRenderPass::PreparePipelineStateForRendering(SharedPtr<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject)
		{
			if (! PipelineState)
			{
				return;
			}

			set<string> const UnboundUniforms = PipelineState->GetUnboundUniforms();

			std::for_each(UnboundUniforms.begin(), UnboundUniforms.end(), [&](string const & Name)
			{
				int Index = -1;
				string LHS, Remaining;

				if (Name == "uModelMatrix")
				{
					PipelineState->SetUniform(Name, uModelMatrix);
				}
				else if (Name == "uNormalMatrix")
				{
					PipelineState->SetUniform(Name, uNormalMatrix);
				}
				else if (Name == "uViewMatrix")
				{
					PipelineState->SetUniform(Name, uViewMatrix);
				}
				else if (Name == "uProjectionMatrix")
				{
					PipelineState->SetUniform(Name, uProjectionMatrix);
				}
				else if (Name == "uCameraPosition")
				{
					PipelineState->SetUniform(Name, uCameraPosition);
				}
				else if (IsUniformNameArrayElement(Name, Index, LHS, Remaining))
				{
					if (Remaining.size() && Remaining[0] == '.')
					{
						auto const it = LightUniformMatrix.find(LHS);
						if (it != LightUniformMatrix.end())
						{
							if (Index < it->second.Entries.size())
							{
								auto const jt = it->second.Entries[Index].find(Remaining.substr(1));
								if (jt != it->second.Entries[Index].end())
								{
									PipelineState->SetUniform(Name, jt->second);
								}
							}
						}
					}
				}
				else
				{
					for (auto & it : LightUniformMatrix)
					{
						string const CountName = it.first + "Count";
						if (Name == CountName)
						{
							PipelineState->SetUniform(Name, it.second.CountUniform);
						}
					}
				}
			});

			PipelineState->Load();
		}

		void CRenderPass::SubmitPipelineStateForRendering(SharedPtr<Graphics::IPipelineState> PipelineState, ISceneObject * SceneObject, uint const InstanceCount, uint const RenderCategory)
		{
			if (! PipelineState)
			{
				return;
			}

			if (RenderCategory >= RenderQueue.size())
			{
				RenderQueue.resize(RenderCategory + 1);
			}
			RenderQueue[RenderCategory].push_back(std::make_tuple(SceneObject, PipelineState, InstanceCount));
		}

		void CRenderPass::RebuildLightUniformMatrix()
		{
			LightUniformMatrix.clear();

			std::for_each(Lights.begin(), Lights.end(), [&](ILight * Light)
			{
				string const LightType = string("u") + Light->GetLightType() + string("s");
				map<string, SharedPtr<Graphics::IUniform>> const LightAttributes = Light->GetAttributes();

				SLightUniformMatrixRow & LightUniformMatrixRow = LightUniformMatrix[LightType];
				LightUniformMatrixRow.Entries.push_back(map<string, SharedPtr<Graphics::IUniform>>());
				LightUniformMatrixRow.CountUniform->Value += 1;
				map<string, SharedPtr<Graphics::IUniform>> & LightUniformMatrixRowEntry = LightUniformMatrixRow.Entries.back();
				
				std::for_each(LightAttributes.begin(), LightAttributes.end(), [&](pair<string, SharedPtr<Graphics::IUniform>> Iterator)
				{
					LightUniformMatrixRowEntry[Iterator.first] = Iterator.second;
				});
			});
		}

	}
}
