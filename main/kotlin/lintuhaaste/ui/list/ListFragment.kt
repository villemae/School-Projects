package lintuhaaste.ui.list

import android.annotation.SuppressLint
import android.os.Bundle
import android.util.Log
import android.view.LayoutInflater
import android.view.View
import android.view.ViewGroup
import android.widget.SearchView
import android.widget.Toast
import androidx.fragment.app.Fragment
import androidx.fragment.app.activityViewModels
import androidx.recyclerview.widget.LinearLayoutManager
import lintuhaaste.R
import lintuhaaste.data.ListViewModel
import lintuhaaste.data.SightingListAdapter
import lintuhaaste.databinding.FragmentListBinding

class ListFragment : Fragment() {

    private val listViewModel: ListViewModel by activityViewModels()
    private var _binding: FragmentListBinding? = null

    private val binding get() = _binding!!

    @SuppressLint("SetTextI18n", "SimpleDateFormat")
    override fun onCreateView(
        inflater: LayoutInflater,
        container: ViewGroup?,
        savedInstanceState: Bundle?
    ): View {

        Log.d("ListFragment", "OnCreateView kutsuttu")
        _binding = FragmentListBinding.inflate(inflater, container, false)
        val root: View = binding.root

        // Initialize RecyclerView
        val recyclerView = binding.recyclerview
        val adapter = SightingListAdapter()
        recyclerView.adapter = adapter
        recyclerView.layoutManager = LinearLayoutManager(requireContext())

        // Query data from Firestore
        listViewModel.changeQuery()

        // Copy the database data in a list
        listViewModel.filteredList.addAll(listViewModel.allSightings)

        adapter.submitList(listViewModel.filteredList)

        // Listen on what item is clicked and navigate accordingly
        adapter.setOnItemClickListener( object: SightingListAdapter.OnItemClickListener {
            override fun onItemClick(position: Int) {
                listViewModel.setCurrent(listViewModel.filteredList[position])
                Log.d("ListFragment", listViewModel.filteredList[position].getSpecies())
                listViewModel.navController.navigate(R.id.action_navigation_list_to_detailsFragment)
            }

        })

        binding.searchBar.setOnQueryTextListener(object: SearchView.OnQueryTextListener {
            // Actions on search word in a search bar
            override fun onQueryTextSubmit(query: String?): Boolean {
                binding.searchBar.clearFocus()
                if (listViewModel.filteredList.size == 0) {
                    Toast.makeText(
                        context, "Havaintoa '$query' ei löydy listalta", Toast.LENGTH_SHORT).show()
                }
                return false
            }

            // Show items in a list which include the search word 
            override fun onQueryTextChange(query: String?): Boolean {
                val search = query!!.lowercase()
                if (search.isNotEmpty()) {
                    listViewModel.filteredList.clear()
                    listViewModel.allSightings.forEach {
                        if (it.getSpecies().contains(search)) {
                            Log.d("ListFragment", it.getSpecies())
                            listViewModel.filteredList.add(it)
                        }
                    }
                    recyclerView.layoutManager = LinearLayoutManager(requireContext())
                } else {
                    listViewModel.filteredList.clear()
                    listViewModel.filteredList.addAll(listViewModel.allSightings)
                    recyclerView.layoutManager = LinearLayoutManager(requireContext())
                    }
                return false
            }
        })

        val sightings = listViewModel.allSightings.size.toString()
        Log.d("ListFragment", sightings)

        // TextView for showing the recognized bird species
        binding.sightingsNumberView.text = resources.getString(R.string.bird_amount) +
                " $sightings / 100"

        return root
    }

    override fun onDestroyView() {
        Log.d("ListFragment", "OnDestroyView kutsuttu")
        super.onDestroyView()
        _binding = null
    }
}