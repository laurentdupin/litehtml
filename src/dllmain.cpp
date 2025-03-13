#include <dllmain.h>

#include <html.h>
#include <mutex>
#include <unordered_map>

static std::mutex LiteHTMLMutex;

struct LiteHTMLContextData
{
    std::vector<std::string> FontList;
    std::unique_ptr<std::vector<LiteHTMLDrawCall>> DrawCalls = std::make_unique<std::vector<LiteHTMLDrawCall>>();
};

static std::unordered_map<std::string, LiteHTMLContextData> ContextDictionary;

class DocumentContainer : public litehtml::document_container
{
private:
    int Width = 0;
    int Height = 0;
	std::string ContextName = "";

    //Copied value from context
    std::vector<std::string> FontList;

public:
	DocumentContainer(const std::string &contextname, const int width, int height) : 
        litehtml::document_container(), 
        Width(width), 
        Height(height),
        ContextName(contextname)
    {
	    LiteHTMLMutex.lock();
	    if (ContextDictionary[ContextName].FontList.size() <= 0)
        {
            FontList.push_back("Default");
        }
        else
        {
            FontList = ContextDictionary[ContextName].FontList;
        }
        
	    LiteHTMLMutex.unlock();
    }
    
    virtual litehtml::uint_ptr create_font(const char* faceName, int size, int weight, litehtml::font_style italic, unsigned int decoration, litehtml::font_metrics* fm)
    {
        return 1;
    }
    
    virtual void delete_font(litehtml::uint_ptr hFont)
    {
    
    }
    
    virtual int text_width(const char* text, litehtml::uint_ptr hFont)
    {
        return (int)strlen(text) * 15;
    }
    
    virtual void draw_text(litehtml::uint_ptr hdc, const char* text, litehtml::uint_ptr hFont, litehtml::web_color color, const litehtml::position& pos)
    {
        LiteHTMLMutex.lock();
        auto &drawcall = ContextDictionary[ContextName].DrawCalls->emplace_back();
        drawcall.DrawCallType = LiteHTMLDrawCallType::TEXT;
        drawcall.Text = text;
        LiteHTMLMutex.unlock();
    }
    
    virtual int pt_to_px(int pt) const
    { 
        return 72 * pt / 96 ;
    }
    
    virtual int get_default_font_size() const
    {
        return 16;
    }
    
    virtual const char* get_default_font_name() const
    {        
        return FontList[0].c_str();
    }
    
    virtual void draw_list_marker(litehtml::uint_ptr hdc, const litehtml::list_marker& marker)
    {
    
    }
    
    virtual void load_image(const char* src, const char* baseurl, bool redraw_on_ready)
    {
    
    }
    
    virtual void get_image_size(const char *src, const char *baseurl, litehtml::size &sz) 
    {
    
    }
    
    virtual void draw_image(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const std::string &url, const std::string &base_url) 
    {
    
    }
    
    virtual void draw_solid_fill(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::web_color &color)	
    {
    
    }
    
    virtual void draw_linear_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::background_layer::linear_gradient &gradient) 
    {
    
    }
    
    virtual void draw_radial_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::background_layer::radial_gradient &gradient) 
    {
    
    }
    
    virtual void draw_conic_gradient(litehtml::uint_ptr hdc, const litehtml::background_layer &layer, const litehtml::background_layer::conic_gradient &gradient) 
    {
    
    }
    
    virtual void draw_borders(litehtml::uint_ptr hdc, const litehtml::borders &borders, const litehtml::position &draw_pos, bool root) 
    {
    
    }
    
    virtual void set_caption(const char *caption) 
    {
    
    }
    
    virtual void set_base_url(const char *base_url) 
    {
    
    }
    
    virtual void link(const std::shared_ptr<litehtml::document> &doc, const litehtml::element::ptr &el) 
    {
    
    }
    
    virtual void on_anchor_click(const char *url, const litehtml::element::ptr &el) 
    {
    
    }
    
    virtual void on_mouse_event(const litehtml::element::ptr &el, litehtml::mouse_event event)	  
    {
    
    }
    
    virtual void set_cursor(const char *cursor) 
    {
    
    }
    
    virtual void transform_text(litehtml::string &text, litehtml::text_transform tt) 
    {
    
    }
    
    virtual void import_css(litehtml::string &text, const litehtml::string &url, litehtml::string &baseurl) 
    {
    
    }
    
    virtual void set_clip(const litehtml::position &pos, const litehtml::border_radiuses &bdr_radius) 
    {
    
    }
    
    virtual void del_clip() 
    {
    
    }
    
    virtual void get_client_rect(litehtml::position &client) const 
    {
        client.x = 0;
        client.y = 0;
        client.width = Width;
        client.height = Height;
    }
    
    virtual litehtml::element::ptr create_element(const char *tag_name, const litehtml::string_map &attributes, const std::shared_ptr<litehtml::document> &doc) 
    {
        return 0;
    }   
    
    virtual void get_media_features(litehtml::media_features &media) const 
    {
    
    }
    
    virtual void get_language(litehtml::string &language, litehtml::string &culture) const 
    {
    
    }
    
    virtual litehtml::string resolve_color(const litehtml::string &color) const 
    {
        return "black";
    }
    
    virtual void split_text(const char *text, const std::function<void(const char *)> &on_word, const std::function<void(const char *)> &on_space) 
    {
	    on_word(text);
    }
};

extern "C" 
{
    __declspec(dllexport) int CreateLiteHTMLContext(const char* contextname)
    {
        auto stdname = std::string(contextname);

        LiteHTMLMutex.lock();
        if (ContextDictionary.find(stdname) != ContextDictionary.end())
        {
            LiteHTMLMutex.unlock();
            return 0;
        }

        ContextDictionary.try_emplace(stdname);
		LiteHTMLMutex.unlock();
        return 1;
    }

    __declspec(dllexport) int DeleteLiteHTMLContext(const char* contextname)
    {
        auto stdname = std::string(contextname);

        LiteHTMLMutex.lock();
        if (ContextDictionary.find(stdname) == ContextDictionary.end())
        {
            LiteHTMLMutex.unlock();
            return 0;
        }

        ContextDictionary.erase(stdname);
		LiteHTMLMutex.unlock();
        return 1;
    }

    __declspec(dllexport) int ClearFontsFromContext(const char* contextname)
    {
        auto stdname = std::string(contextname);

        LiteHTMLMutex.lock();
		if (ContextDictionary.find(stdname) == ContextDictionary.end())
        {
            LiteHTMLMutex.unlock();
            return 0;
        }

        ContextDictionary[stdname].FontList.clear();
        LiteHTMLMutex.unlock();
    }

    __declspec(dllexport) int AddFontToContext(const char* contextname, const char* font)
    {
	    auto stdname = std::string(contextname);

        LiteHTMLMutex.lock();
		if (ContextDictionary.find(stdname) == ContextDictionary.end())
        {
            LiteHTMLMutex.unlock();
            return 0;
        }

        ContextDictionary[stdname].FontList.push_back(std::string(font));
        LiteHTMLMutex.unlock();
    }

    __declspec(dllexport) int GenerateDrawCalls(const char* contextname, const char *page, const char* css, int width, int height, int clipx, int clipy, int clipwidth, int clipheight) 
    {
        auto stdname = std::string(contextname);

        LiteHTMLMutex.lock();
		if (ContextDictionary.find(stdname) == ContextDictionary.end())
        {
            LiteHTMLMutex.unlock();
            return 0;
        }

        ContextDictionary[stdname].DrawCalls->clear();
        LiteHTMLMutex.unlock();

        DocumentContainer container(stdname, width, height);
        auto pagestring = litehtml::estring(page);
		auto cssstring = litehtml::estring(css);
		litehtml::position clip{clipx, clipy, clipwidth, clipheight};

        auto doc = litehtml::document::createFromString(pagestring, &container, litehtml::master_css, cssstring);
		doc->render(width);
        doc->draw(0, 0, 0, &clip);

        return 1;
    }

    __declspec(dllexport) LiteHTMLDrawCall* GetDrawCall(const char* contextname, int callindex)
    {
        if(callindex < 0)
        {
            return NULL;
        }

        auto stdname = std::string(contextname);

        LiteHTMLMutex.lock();
        if (ContextDictionary.find(stdname) == ContextDictionary.end() || ContextDictionary[stdname].DrawCalls->size() <= callindex)
        {
            LiteHTMLMutex.unlock();
            return NULL;
        }

        auto returnptr = &ContextDictionary[stdname].DrawCalls->at(callindex);
        LiteHTMLMutex.unlock();

        return returnptr;
    }

}