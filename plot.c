#include <TCanvas.h>
#include <TGraph.h>

void plot() {
     
     // Create a canvas to display the graph
     gStyle->SetOptFit();
     TCanvas *canvas = new TCanvas("canvas", "Graph", 800, 600); 
     TCanvas *canvas_1 = new TCanvas("canvas_1", "Graph_1", 800, 600);      

    // Data
     const int n = 10;
   
     const int beam= 1;
    
     if (beam == 1){
        double evnt[n] = {4535,4427,4486,4456,4414,4407,4406,4499,4487,4309};
        double thickness_1[n] = {1,2,3,4,5,6,7,8,9,10};

        double eff[n] = {0.004535,0.004427,0.004486,0.004456,0.004414,0.004407,0.004406,0.004499,0.004487,0.004309};
        

        // Create a TGraph object
        TGraph *graph = new TGraph(n, thickness, evnt);
        TGraph *graph_1 = new TGraph(n, thickness_1, eff);

        // Set the graph title and axis labels
        graph->SetTitle("Graph of evnt vs thickness");
        graph->GetXaxis()->SetTitle("thickness[mm]");
        graph->GetYaxis()->SetTitle("evnt");

        // set graph for efficiency
        graph_1->SetTitle("Efficiency vs thickness");
        graph_1->GetXaxis()->SetTitle("thickness[mm]");
        graph_1->GetYaxis()->SetTitle("efficiency");

        // Draw the graph
        canvas->cd();
        graph->Draw("apl*");  // "AP" option specifies drawing with markers (points) and connecting with lines
        graph->SetMarkerColor(kBlue);
        graph->SetMarkerSize(1);


        // Draw the graph
        canvas_1->cd();
        graph_1->Draw("apl*");  // "AP" option specifies drawing with markers (points) and connecting with lines
        graph_1->SetMarkerColor(kBlack);
        graph_1->SetMarkerSize(1);
        canvas_1->Draw();
     }

}

